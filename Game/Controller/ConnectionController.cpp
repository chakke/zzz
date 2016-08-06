

#include "ConnectionController.hpp"

#include "../../Utils/Functions.hpp"
#include "../../Network/AppConnectorBuilder.hpp"
#include "../../Data/ObserverData.hpp"
#include "../../Data/AppString.hpp"
#include "../../Game/GameModel/Cache.hpp"
#include "../../Data/AppConfiguration.hpp"
#include "../../Utils/DeviceInfo.h"
#include "../../Network/AppConnectorConfig.hpp"
#include "json/document.h"
#include "../../Utils/Log.h"
#include "ToastController.hpp"

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#define strncasecmp _strnicmp
#define strcasecmp _stricmp
#endif


namespace connection_controller
{
#ifdef REGISTERING
#undef REGISTERING
#endif
	enum State
	{
		NONE,
		CONNECTING,
		CONNECTED,
		CONNECTING_TO_REGISTER,
		CONNECTED_TO_REGISTER,
		LOGINING_TO_REGISTER,
		LOGINED_TO_REGISTER,
		LOGINING,
		LOGINED,
		REGISTERING,
		REGISTED
	};

	struct custom_data
	{
		custom_data()
		{
			_state = NONE;
		}

		std::string _account;
		std::string _password;
		game_model::user_type _type;

		State _state;
		std::unordered_map<int, std::function<void(network_data* ref, ConnectionController* controller)>> _apiDelegates;
	};

	std::unordered_map<int, custom_data*> __custom_datas__;

	/*
	 *
	 *  network output delegates
	 *
	 */
	void on_connect_output(network_data* ref, ConnectionController* controller)
	{
		custom_data* data = __custom_datas__.at(controller->_id);
		connect_output* output = (connect_output*)ref;

		if (data->_state == CONNECTING)
		{
			if (output->_result.compare(app_string::__CONNECTED__) == 0)
			{
				Log::d("Connected, now login to server");
				data->_state = CONNECTED;
				data->_state = LOGINING;
				auto login_input = new struct login_input();
				login_input->_username = data->_account;
				login_input->_password = data->_password;
				/*login_input->_type = data->_type;
				login_input->_partner_id = app_configuration::__PARTNER_ID__;
				login_input->_ref_code = app_configuration::__REF_CODE__;
				login_input->_imei = DeviceInfo::getDeviceID();
				login_input->_version_code = app_configuration::__VERSION_CODE__;*/
				controller->sendData(login_input);

			}
			else
			{
				data->_state = NONE;
				ToastController::getInstance()->toast(app_string::getValueMap("strings/login.plist")->at("CONNECT_FAILED").asString(), 4.0);
				Log::d("connect fail");
			}
		}
		else if (data->_state == CONNECTING_TO_REGISTER)
		{
			if (output->_result.compare(app_string::__CONNECTED__) == 0)
			{
				data->_state = CONNECTED_TO_REGISTER;

				Log::d("Connected ! now login as guest");

				data->_state = LOGINING_TO_REGISTER;
				auto login_input = new struct login_input();
				login_input->_username = "";
				login_input->_password = "";
				//login_input->_type = data->_type;
				/*login_input->_partner_id = app_configuration::__PARTNER_ID__;
				login_input->_ref_code = app_configuration::__REF_CODE__;
				login_input->_imei = DeviceInfo::getDeviceID();
				login_input->_version_code = app_configuration::__VERSION_CODE__;*/
				controller->sendData(login_input);

			}
			else
			{
				data->_state = NONE;
				ToastController::getInstance()->toast(app_string::getValueMap("strings/login.plist")->at("CONNECT_FAILED").asString(), 2.0);
				//FIXME
				Log::d("connect to register failed");
			}
		}
	}

	void on_login_output(network_data* ref, ConnectionController* controller)
	{
		custom_data* data = __custom_datas__.at(controller->_id);
		if (data->_state == LOGINING_TO_REGISTER)
		{
			login_output* output = (login_output*)ref;
			if (output->_result.compare(app_string::__SUCCESS__) == 0)
			{
				data->_state = LOGINED_TO_REGISTER;
				//Log::d("logined by guest account, now register acount : %s with password : %s",data->_account.c_str(),data->_password.c_str());
				data->_state = REGISTERING;
				auto input = new extension_data();
				input->_cmd = cmd::__ZONE__ + "." + cmd::__REGISTER__;
				input->_object.putString(extparamskey::__USER_NAME__, data->_account);
				input->_object.putString(extparamskey::__PASSWORD__, data->_password);
				/*input->_object.putInt(extparamskey::__PARTNER_ID__, app_configuration::__PARTNER_ID__);
				input->_object.putString(extparamskey::__REF_CODE__, app_configuration::__REF_CODE__);
				input->_object.putString(extparamskey::__PLATFORM__, DeviceInfo::getPlatform() + " - " + DeviceInfo::getDeviceName());
				input->_object.putInt(extparamskey::__TYPE__, app_configuration::__APP_TYPE__);
				input->_object.putString(extparamskey::__IMEI__, DeviceInfo::getDeviceID());*/
				input->_sendRoom = false;
				controller->sendData(input);
			}
			else
			{
				Log::d("login to register fail");
				data->_state = NONE;
				if (controller->getLoginCallback())
				{
					controller->getLoginCallback()(app_string::__FAIL__);
				}
				auto input = new disconnect_input();
				controller->sendData(input);
			}
		}
		else if (data->_state == LOGINING)
		{
			login_output* output = (login_output*)ref;
			if (output->_result.compare(app_string::__SUCCESS__) == 0)
			{
				
				if (!output->_guest_acount.empty() && data->_type == game_model::__QUICK__)
				{
					Log::d("on login success as guest : %s", output->_guest_acount.c_str());
					data->_state = LOGINED;
					game_model::__user_cache__->_name = output->_guest_acount;
					game_model::__user_cache__->_account = output->_guest_acount;
					game_model::__user_cache__->_password = "";
					game_model::__user_cache__->_type = game_model::__QUICK__;
					game_model::__user_cache__->_avatar_url = "0";
					game_model::save_user_cache();
					if (controller->getLoginCallback())
					{
						controller->getLoginCallback()(app_string::__SUCCESS__);
					}
				}
				else if (data->_type == game_model::__USER__)
				{
					Log::d("on login success as ", data->_account.c_str());
					data->_state = LOGINED;
					game_model::__user_cache__->_account = data->_account;
					game_model::__user_cache__->_password = data->_password;
					game_model::__user_cache__->_type = game_model::__USER__;
					game_model::__user_cache__->_avatar_url = "0";
					game_model::save_user_cache();
					if (controller->getLoginCallback())
					{
						controller->getLoginCallback()(app_string::__SUCCESS__);
					}
				}
			}
			else
			{
				Log::d("on login error, now disconnect");
				data->_state = NONE;
				if (controller->getLoginCallback())
				{
					controller->getLoginCallback()(app_string::__FAIL__);
				}
				auto input = new disconnect_input();
				controller->sendData(input);
			}
		}
	}

	void on_log_out_output(network_data* ref, ConnectionController* controller)
	{
		custom_data* custom_data = __custom_datas__.at(controller->_id);
		if (custom_data->_state == REGISTED)
		{
			//Log::d(StringUtils::format("logout success, now login with account created : %s %s", custom_data->_account.c_str(), custom_data->_password.c_str()));
			custom_data->_state = LOGINING;
			auto login_input = new struct login_input();
			login_input->_username = custom_data->_account;
			login_input->_password = custom_data->_password;
			/*login_input->_type = custom_data->_type;
			login_input->_partner_id = app_configuration::__PARTNER_ID__;
			login_input->_ref_code = app_configuration::__REF_CODE__;
			login_input->_imei = DeviceInfo::getDeviceID();
			login_input->_version_code = app_configuration::__VERSION_CODE__;*/
			controller->sendData(login_input);
		}
	}

	void on_extension_data_output(network_data* ref, ConnectionController* controller)
	{
		custom_data* custom_data = __custom_datas__.at(controller->_id);

		auto data = dynamic_cast<extension_data*>(ref);
		if (data)
		{
			if (data->_cmd.compare(cmd::__GET_USER_INFO__) == 0)
			{
				
			}
			else if (data->_cmd.compare(cmd::__REGISTER__) == 0)
			{
				if (data->_object.getBool(extparamskey::__IS_SUCCESS__))
				{
					custom_data->_state = REGISTED;
					Log::d("register success, now log out ...");
					if (controller->getRegisterCallback())
					{
						controller->getRegisterCallback()(app_string::__SUCCESS__);
					}
					auto input = new log_out_input();
					controller->sendData(input);
				}
				else
				{

					Log::d("register error, disconnect ...");
					custom_data->_state = NONE;
					if (controller->getRegisterCallback())
					{
						controller->getRegisterCallback()(*data->_object.getString(extparamskey::__REASON__));
					}
					auto input = new disconnect_input();
					controller->sendData(input);
				}
			}
		}
	}

	void on_join_room_output(network_data* ref, ConnectionController* controller)
	{
		auto data = dynamic_cast<join_room_output*>(ref);
		controller->_current_room = data->_notity_room_name;
	}

	/* config delegates */
	void on_get_config(bool ret, std::string response, ConnectionController* controller)
	{
		bool maintainance = false;
		rapidjson::Document doc;
		doc.Parse<0>(response.c_str());
		if (!doc.HasParseError())
		{
			if (doc.HasMember("maintainance"))
			{
				if (doc["maintainance"].IsBool())
				{
					maintainance = doc["maintainance"].GetBool();
				}
				else if (doc["maintainance"].IsString())
				{
					maintainance = strcasecmp(doc["maintainance"].GetString(), "true") == 0;
				}
			}
			if (doc.HasMember("server_primary_host"))
			{
				app_configuration::__HOST__ = doc["server_primary_host"].GetString();
			}
			if (doc.HasMember("zone"))
			{
				app_configuration::__ZONE_GAME__ = doc["zone"].GetString();
			}
			if (doc.HasMember("server_primary_port"))
			{
				if (doc["server_primary_port"].IsInt())
				{
					app_configuration::__SOCKET_PORT_TCP__ = doc["server_primary_port"].GetInt();
				}
				else if (doc["server_primary_port"].IsString())
				{
					app_configuration::__SOCKET_PORT_TCP__ = atoi(doc["server_primary_port"].GetString());
				}
			}
			if (app_configuration::__HOST__.size() <= 1)
			{
				if (doc.HasMember("server_backup_host"))
				{
					app_configuration::__HOST__ = doc["server_backup_host"].GetString();
				}
				if (doc.HasMember("server_backup_port"))
				{
					if (doc["server_backup_port"].IsInt())
					{
						app_configuration::__SOCKET_PORT_TCP__ = doc["server_backup_port"].GetInt();
					}
					else if (doc["server_backup_port"].IsString())
					{
						app_configuration::__SOCKET_PORT_TCP__ = atoi(doc["server_backup_port"].GetString());
					}
				}
			}
			if (doc.HasMember("upload_avatar"))
			{
				std::string uploadFileUri = doc["upload_avatar"].GetString();
				if (uploadFileUri.size() > 1)
				{
					app_configuration::__UPLOAD_URI__ = uploadFileUri;
				}
			}
			if (doc.HasMember("payment_permission"))
			{
				if (doc["payment_permission"].IsBool())
				{
					app_configuration::__PAYMENT_PERMISSION__ = doc["payment_permission"].GetBool();
				}
				else if (doc["payment_permission"].IsString())
				{
					app_configuration::__PAYMENT_PERMISSION__ = strcasecmp(doc["payment_permission"].GetString(), "true") == 0;
				}
			}
			if (doc.HasMember("payment_method"))
			{
				rapidjson::Value& payment_method = doc["payment_method"];
				for (int i = 0; i < payment_method.Size(); i++)
				{
					std::string method = payment_method[i].GetString();
					if (method.compare("PAYMENT_CARD") == 0)
					{
						app_configuration::__PAYMENT_CARD__ = true;
					}
					else if (method.compare("PAYMENT_SMS") == 0)
					{
						app_configuration::__PAYMENT_SMS__ = true;
					}
					else if (method.compare("PAYMENT_IAP") == 0)
					{
						app_configuration::__PAYMENT_IAP__ = true;
					}
				}
			}

			if (doc.HasMember("verify_appstore"))
			{
				if (doc["verify_appstore"].IsBool())
				{
					app_configuration::__VERIFY_APPSTORE__ = doc["verify_appstore"].GetBool();
				}
				else if (doc["verify_appstore"].IsString())
				{
					app_configuration::__VERIFY_APPSTORE__ = strcasecmp(doc["verify_appstore"].GetString(), "true") == 0;
				}
			}
		}

		if (maintainance && controller->getMaintainanceCallback())
		{
			controller->getMaintainanceCallback()();
		}
	}

}

static ConnectionController* _instance = nullptr;

ConnectionController* ConnectionController::getInstance()
{
	if (!_instance)
	{
		_instance = ConnectionController::create();
		CC_SAFE_RETAIN(_instance);
	}
	return _instance;
}

bool ConnectionController::init()
{
	_current_room = app_configuration::__LOBBY_ROOM__;
	_maintainanceCallback = nullptr;
	_loginCallback = nullptr;

	auto data = new connection_controller::custom_data();
	connection_controller::__custom_datas__.insert(std::make_pair(_id, data));

	data->_apiDelegates.insert(std::make_pair(connect_output()._id, std::bind(connection_controller::on_connect_output, std::placeholders::_1, this)));
	data->_apiDelegates.insert(std::make_pair(login_output()._id, std::bind(connection_controller::on_login_output, std::placeholders::_1, this)));
	data->_apiDelegates.insert(std::make_pair(log_out_output()._id, std::bind(connection_controller::on_log_out_output, std::placeholders::_1, this)));
	data->_apiDelegates.insert(std::make_pair(extension_data()._id, std::bind(connection_controller::on_extension_data_output, std::placeholders::_1, this)));
	data->_apiDelegates.insert(std::make_pair(join_room_output()._id, std::bind(connection_controller::on_join_room_output, std::placeholders::_1, this)));

	return true;
}

void ConnectionController::onRemove()
{
	//    unscheduleUpdate();
	AppConnectorBuilder::getInstance()->removeDestination(this);
	removeDestination(AppConnectorBuilder::getInstance());
}

void ConnectionController::onLinked()
{
	//    scheduleUpdate();
	AppConnectorBuilder::getInstance()->addDestination(this);
	addDestination(AppConnectorBuilder::getInstance());
}

void ConnectionController::update(float delta)
{

}

void ConnectionController::listen(Observer* sender, cocos2d::Ref* ref)
{
	connection_controller::custom_data* data = connection_controller::__custom_datas__.at(_id);

	auto rdata = dynamic_cast<network_data*>(ref);
	if (rdata)
	{
		if (data->_apiDelegates.find(rdata->_id) != data->_apiDelegates.end())
		{
			data->_apiDelegates.at(rdata->_id)(rdata, this);
		}

		return;
	}
}

void ConnectionController::setLoginCallback(const OnLoginCallback& callback)
{
	_loginCallback = callback;
}

void ConnectionController::setRegisterCallback(const OnRegisterCallback & callback)
{
	this->_registerCallback = callback;
}

void ConnectionController::setMaintainanceCallback(const OnMaintainanceCallback& callback)
{
	_maintainanceCallback = callback;
}

void ConnectionController::disconnect(bool removeUserNameAndPass)
{
	connection_controller::custom_data* data = connection_controller::__custom_datas__.at(_id);
	data->_state = connection_controller::NONE;

	auto input = new disconnect_input();
	sendData(input);

	data->_account = "";
	data->_password = "";
	data->_type = 0;
	if (removeUserNameAndPass) {
		game_model::__user_cache__->_account = "";
		game_model::__user_cache__->_password = "";
	}
	game_model::__user_cache__->_money = 0;
	game_model::__user_cache__->_avatar_url = "";
	game_model::__user_cache__->_name = "";
	game_model::__user_cache__->_joined_room_name = "";
	game_model::__user_cache__->_joined_room_id = -1;
	game_model::save_user_cache();
}


void ConnectionController::login(const game_model::user_type& type, const std::string& account, const std::string& password)
{
	connection_controller::custom_data* data = connection_controller::__custom_datas__.at(_id);

	if (data->_state == connection_controller::NONE)
	{
		data->_account = account;
		data->_password = password;
		data->_type = type;
		data->_state = connection_controller::CONNECTING;

		game_model::__user_cache__->_account = account;
		game_model::__user_cache__->_password = password;
		game_model::save_user_cache();

		sendData(new connect_input());
	}
}

void ConnectionController::registerAccount(const std::string& account, const std::string& password)
{
	connection_controller::custom_data* data = connection_controller::__custom_datas__.at(_id);
	if (data->_state == connection_controller::NONE)
	{
		data->_account = account;
		data->_password = password;
		data->_type = game_model::__USER__;
		data->_state = connection_controller::CONNECTING_TO_REGISTER;
		sendData(new connect_input());
	}
}

void ConnectionController::get_user_info()
{
	connection_controller::custom_data* data = connection_controller::__custom_datas__.at(_id);
	if (data->_state == connection_controller::LOGINED)
	{
		auto input = new extension_data();
		/*input->_object.putString(extparamskey::__NICK_NAME__, game_model::__user_cache__->_name);
		input->_object.putString(extparamskey::__AVATAR__, game_model::__user_cache__->_avatar_url);
		input->_object.putString(extparamskey::__PACKAGE_GAME__, app_configuration::__PACKAGE_NAME__);
		input->_object.putString(extparamskey::__VERSION_, app_configuration::__VERSION_CODE__);
		input->_object.putString(extparamskey::__PLATFORM__, DeviceInfo::getPlatform() + " - " + DeviceInfo::getDeviceName());
		input->_object.putInt(extparamskey::__PARTNER_ID__, app_configuration::__PARTNER_ID__);
		input->_object.putInt(extparamskey::__TYPE__, app_configuration::__APP_TYPE__);
		input->_object.putString(extparamskey::__PROTOCOL__, AppConnectorBuilder::getInstance()->isUdp() ? "udp" : "tcp");*/
		input->_cmd = cmd::__ZONE__ + "." + cmd::__GET_USER_INFO__;

		sendData(input);
	}
}
