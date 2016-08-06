
#include "SmartFoxAppConnector.hpp"
#include "SmartFox.h"
#include "Requests/LoginRequest.h"
#include "Requests/ExtensionRequest.h"
#include "Requests/JoinRoomRequest.h"
#include "Requests/LeaveRoomRequest.h"
#include "Requests/LogoutRequest.h"
#include "../../Utils/Functions.hpp"
#include "../../Data/ObserverData.hpp"
#include "../../Data/AppString.hpp"
#include "../../Data/AppConfiguration.hpp"
#include "../AppConnectorConfig.hpp"
#include "../../Game/GameModel/Cache.hpp"
#include "../../Utils/DeviceInfo.h"
#include "../../Game/GameModel/GameType.hpp"
#include "../../Config/Config.hpp"
#include "ctpl_stl.h"

USING_NS_CC;

enum class AppConnectorEnum
{
	__APP_CONNECTOR_DELEGATE__,
	__USER_ROOM__
};
connection_array convertSMFArray(boost::shared_ptr<ISFSArray> sfsarray);
connection_object convertSMFObject(boost::shared_ptr<ISFSObject> sfsobject);

connection_array convertSMFArray(boost::shared_ptr<ISFSArray> sfsarray)
{
	connection_array array;
	array._array.reserve(sfsarray->Size());
	for (int i = 0; i < sfsarray->Size(); i++)
	{
		boost::shared_ptr<SFSDataWrapper> data = sfsarray->GetWrappedElementAt(i);
		long int type = data->Type();
		switch (type)
		{
		case SFSDATATYPE_NULL:

			break;
		case SFSDATATYPE_BOOL:
			array.pushBool(sfsarray->GetBool(i));
			break;
		case SFSDATATYPE_BYTE:
			array.pushByte(sfsarray->GetByte(i));
			break;
		case SFSDATATYPE_SHORT:
			array.pushShort(sfsarray->GetShort(i));
			break;
		case SFSDATATYPE_INT:
			array.pushInt(sfsarray->GetInt(i));
			break;
		case SFSDATATYPE_LONG:
			array.pushLong(sfsarray->GetLong(i));
			break;
		case SFSDATATYPE_FLOAT:
			array.pushFloat(sfsarray->GetFloat(i));
			break;
		case SFSDATATYPE_DOUBLE:
			array.pushDouble(sfsarray->GetDouble(i));
			break;
		case SFSDATATYPE_UTF_STRING:
			array.pushString(*sfsarray->GetUtfString(i));
			break;
		case SFSDATATYPE_BOOL_ARRAY:
			array.pushBoolArray(*sfsarray->GetBoolArray(i));
			break;
		case SFSDATATYPE_BYTE_ARRAY:
			array.pushByteArray(*sfsarray->GetByteArray(i)->Bytes());
			break;
		case SFSDATATYPE_SHORT_ARRAY:
			array.pushShortArray(*sfsarray->GetShortArray(i));
			break;
		case SFSDATATYPE_INT_ARRAY:
			array.pushIntArray(*sfsarray->GetIntArray(i));
			break;
		case SFSDATATYPE_LONG_ARRAY:
			array.pushLongArray(*sfsarray->GetLongArray(i));
			break;
		case SFSDATATYPE_FLOAT_ARRAY:
			array.pushFloatArray(*sfsarray->GetFloatArray(i));
			break;
		case SFSDATATYPE_DOUBLE_ARRAY:
			array.pushDoubleArray(*sfsarray->GetDoubleArray(i));
			break;
		case SFSDATATYPE_UTF_STRING_ARRAY:
			array.pushStringArray(*sfsarray->GetUtfStringArray(i));
			break;
		case SFSDATATYPE_SFS_ARRAY:
			array.pushArray(convertSMFArray(sfsarray->GetSFSArray(i)));
			break;
		case SFSDATATYPE_SFS_OBJECT:
			array.pushObject(convertSMFObject(sfsarray->GetSFSObject(i)));
			break;
		case SFSDATATYPE_CLASS:
			break;
		}
	}
	return array;
}

connection_object convertSMFObject(boost::shared_ptr<ISFSObject> sfsobject)
{
	connection_object object;

	boost::shared_ptr<std::vector<std::string>> keys = sfsobject->GetKeys();
	for (int i = 0; i < keys->size(); i++)
	{
		const std::string& key = keys->at(i);
		long int type = sfsobject->GetData(key)->Type();
		switch (type)
		{
		case SFSDATATYPE_NULL:

			break;
		case SFSDATATYPE_BOOL:
			object.putBool(key, *sfsobject->GetBool(key));
			break;
		case SFSDATATYPE_BYTE:
			object.putByte(key, *sfsobject->GetByte(key));
			break;
		case SFSDATATYPE_SHORT:
			object.putShort(key, *sfsobject->GetShort(key));
			break;
		case SFSDATATYPE_INT:
			object.putInt(key, *sfsobject->GetInt(key));
			break;
		case SFSDATATYPE_LONG:
			object.putLong(key, *sfsobject->GetLong(key));
			break;
		case SFSDATATYPE_FLOAT:
			object.putFloat(key, *sfsobject->GetFloat(key));
			break;
		case SFSDATATYPE_DOUBLE:
			object.putDouble(key, *sfsobject->GetDouble(key));
			break;
		case SFSDATATYPE_UTF_STRING:
			object.putString(key, *sfsobject->GetUtfString(key));
			break;
		case SFSDATATYPE_BOOL_ARRAY:
			object.putBoolArray(key, *sfsobject->GetBoolArray(key));
			break;
		case SFSDATATYPE_BYTE_ARRAY:
			object.putByteArray(key, *sfsobject->GetByteArray(key)->Bytes());
			break;
		case SFSDATATYPE_SHORT_ARRAY:
			object.putShortArray(key, *sfsobject->GetShortArray(key));
			break;
		case SFSDATATYPE_INT_ARRAY:
			object.putIntArray(key, *sfsobject->GetIntArray(key));
			break;
		case SFSDATATYPE_LONG_ARRAY:
			object.putLongArray(key, *sfsobject->GetLongArray(key));
			break;
		case SFSDATATYPE_FLOAT_ARRAY:
			object.putFloatArray(key, *sfsobject->GetFloatArray(key));
			break;
		case SFSDATATYPE_DOUBLE_ARRAY:
			object.putDoubleArray(key, *sfsobject->GetDoubleArray(key));
			break;
		case SFSDATATYPE_UTF_STRING_ARRAY:
			object.putStringArray(key, *sfsobject->GetUtfStringArray(key));
			break;
		case SFSDATATYPE_SFS_ARRAY:
			object.putArray(key, convertSMFArray(sfsobject->GetSFSArray(key)));
			break;
		case SFSDATATYPE_SFS_OBJECT:
			object.putObject(key, convertSMFObject(sfsobject->GetSFSObject(key)));
			break;
		case SFSDATATYPE_CLASS:
			break;
		}
	}

	return object;
}

//-------------------------------------------------------------------------------
//                                  App Connector Delegate
//-------------------------------------------------------------------------------

class AppConnectorUserRoom : public cocos2d::Ref
{
public:
	static AppConnectorUserRoom* create(boost::shared_ptr<Room> room)
	{
		auto ret = new AppConnectorUserRoom();
		ret->_room = room;
		ret->autorelease();
		return ret;
	}

	boost::shared_ptr<Room> _room;
};

template<typename T>
class AppBaseDelegateResponseSmartFox : public cocos2d::Ref
{
public:
	AppBaseDelegateResponseSmartFox(Observer* observer)
	{
		_observer = observer;
		Ref::autorelease();
	}

	virtual void process(T object) = 0;
	Observer* _observer;
};

#define CREATE_DELEGATE_RESPONSE_SMARTFOX_CONSTRUCTOR(__TYPE__) \
__TYPE__(Observer* observer) : AppBaseDelegateResponseSmartFox(observer) \
{ \
}

class AppConnectorDelegate : public cocos2d::Ref
{
public:

	static AppConnectorDelegate* create(boost::shared_ptr<Sfs2X::SmartFox> smartFox, SmartFoxAppConnector* observer)
	{
		auto ret = new AppConnectorDelegate();
		ret->_smartFox = boost::shared_ptr<Sfs2X::SmartFox>(smartFox);
		ret->_observer = observer;
		ret->autorelease();
		return ret;
	}
	static void onUDPInit(unsigned long long t, boost::shared_ptr<BaseEvent> event)
	{
		AppConnectorDelegate* delegate = (AppConnectorDelegate*)t;

		boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = event->Params();
		boost::shared_ptr<void> ptrEventParamValueSuccess = (*ptrEventParams)["success"];
		if ((*((boost::static_pointer_cast<bool>)(ptrEventParamValueSuccess))) == true)
		{
			CCLOG("Init udp success");
			config::__UDP_STATE__ = 2;
		}
		else
		{
			config::__UDP_STATE__ = 3;
			delegate->_smartFox->Disconnect();
			CCLOG("Init udp error");
		}
	}

	static void onConnection(unsigned long long t, boost::shared_ptr<BaseEvent> event)
	{
		AppConnectorDelegate* delegate = (AppConnectorDelegate*)t;


		boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = event->Params();
		boost::shared_ptr<void> ptrEventParamValueSuccess = (*ptrEventParams)["success"];
		boost::shared_ptr<bool> ptrValue = (boost::static_pointer_cast<bool>)(ptrEventParamValueSuccess);
		if (*ptrValue == true)
		{
			// Connection was established
			auto output = new connect_output();
			output->_result = app_string::__CONNECTED__;
			delegate->_observer->sendData(output);
		}
		else
		{
			// Connection failed
			CCLOG("Connect failed");
			auto output = new connect_output();
			output->_result = app_string::__FAIL__;
			delegate->_observer->sendData(output);
		}

	}

	static void onConnectionLost(unsigned long long t, boost::shared_ptr<BaseEvent> event)
	{
		CCLOG("Connection lost");
		AppConnectorDelegate* delegate = (AppConnectorDelegate*)t;
		auto output = new connect_output();
		output->_result = app_string::__LOST__;
		delegate->_observer->sendData(output);
	}

	static void onConnectionResume(unsigned long long t, boost::shared_ptr<BaseEvent> event)
	{
		CCLOG("connection resume");
	}

	static void onConnectionRetry(unsigned long long t, boost::shared_ptr<BaseEvent> event)
	{
		CCLOG("connection retry");
	}

	static void onLogin(unsigned long long t, boost::shared_ptr<BaseEvent> event)
	{
		AppConnectorDelegate* delegate = (AppConnectorDelegate*)t;
		auto output = new login_output();
		boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = event->Params();
		if (ptrEventParams->find(extparamskey::__DATA__) != ptrEventParams->end())
		{
			boost::shared_ptr<void> ptrEventParamValueData = (*ptrEventParams)[extparamskey::__DATA__];
			boost::shared_ptr<ISFSObject> data = boost::static_pointer_cast<ISFSObject>(ptrEventParamValueData);
			/*if (data && data->ContainsKey(extparamskey::__FS_NEW_LOGIN_NAME__))
			{
				output->_guest_acount = data->GetUtfString(extparamskey::__FS_NEW_LOGIN_NAME__)->c_str();
			}*/
		}

		output->_result = app_string::__SUCCESS__;
		delegate->_observer->sendData(output);

		auto sfs = delegate->_smartFox;
		if (sfs && !sfs->UdpInited()) {
			if (sfs->UdpAvailable()) {
				sfs->InitUDP(app_configuration::__HOST__.c_str(), app_configuration::__SOCKET_PORT_UDP__);
			}
			else {
				CCLOG("========= UDP not available ============");
				config::__UDP_STATE__ = 1;
				delegate->_smartFox->Disconnect();
			}

		}
	}

	static void onLoginError(unsigned long long t, boost::shared_ptr<BaseEvent> event)
	{
		AppConnectorDelegate* delegate = (AppConnectorDelegate*)t;
		auto output = new login_output();
		output->_result = app_string::__FAIL__;

		boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = event->Params();
		boost::shared_ptr<void> ptrEventParamValueMessage = (*ptrEventParams)[app_string::__ERROR_MESSAGE_KEY__];
		boost::shared_ptr<string> ptrNotifiedMessage = boost::static_pointer_cast<string>(ptrEventParamValueMessage);

		if (ptrNotifiedMessage) output->_message = ptrNotifiedMessage->c_str();
		CCLOG("on login error : %s", output->_message.c_str());

		delegate->_observer->sendData(output);
	}

	static void onLogout(unsigned long long t, boost::shared_ptr<BaseEvent> event)
	{
		AppConnectorDelegate* delegate = (AppConnectorDelegate*)t;
		auto output = new log_out_output();
		delegate->_observer->sendData(output);
	}
	static void onPingPong(unsigned long long t, boost::shared_ptr<BaseEvent> event)
	{
		
		if ((*event->Type()).compare(*Sfs2X::Core::SFSEvent::PING_PONG) == 0) {
			AppConnectorDelegate* delegate = (AppConnectorDelegate*)t;

			boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = event->Params();
			boost::shared_ptr<void> value = (*ptrEventParams)[app_string::__LAG_VALUE__];
			
			boost::shared_ptr<int> ptrValue = boost::static_pointer_cast<int>(value);

			auto output = new ping_pong_output();
			output->_lag_time = *ptrValue;
			delegate->_observer->sendData(output);
			CCLOG("on ping pong ........................ %d",*ptrValue);
		}
		
	}

	static void onExtensionResponse(unsigned long long t, boost::shared_ptr<BaseEvent> event)
	{

		AppConnectorDelegate* delegate = (AppConnectorDelegate*)t;

		boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = event->Params();
		boost::shared_ptr<void> ptrEventParamValueCmd = (*ptrEventParams)[app_string::__CMD_KEY__];
		boost::shared_ptr<void> ptrEventParamValueParams = (*ptrEventParams)[app_string::__PARAMS_KEY__];

		boost::shared_ptr<string> cmd = boost::static_pointer_cast<string>(ptrEventParamValueCmd);
		boost::shared_ptr<ISFSObject> params = boost::static_pointer_cast<ISFSObject>(ptrEventParamValueParams);

		extension_data* output = new extension_data();

		output->_object = convertSMFObject(params);
		output->_cmd = *cmd;
		delegate->_observer->sendData(output);
		if (config::__DEBUG_RESPONSE__) {
			if ( cmd->compare("us") != 0 || config::__DEBUG_RESPONSE_POSITION__ ) {
				CCLOG("============ Extension Response ===============");
				CCLOG("CMD : %s", cmd->c_str());
				CCLOG("dum : %s", params->GetDump(true)->c_str());
				CCLOG("===============================================");
			}
		}
	}
	static void onRoomJoinResponse(unsigned long long t, boost::shared_ptr<BaseEvent> event)
	{
		AppConnectorDelegate* delegate = (AppConnectorDelegate*)t;

		boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = event->Params();
		boost::shared_ptr<void> ptrEventParamValueRoom = (*ptrEventParams)["room"];
		boost::shared_ptr<Room> ptrNotifiedRoom = boost::static_pointer_cast<Room>(ptrEventParamValueRoom);
		AppConnectorUserRoom* riderroom = (AppConnectorUserRoom*)delegate->_observer->_refMap.at((int)AppConnectorEnum::__USER_ROOM__);
		riderroom->_room = ptrNotifiedRoom;

		auto output = new join_room_output();
		output->_notity_room_name = ptrNotifiedRoom->Name()->c_str();
		delegate->_observer->sendData(output);
	}

	static void onRoomLeaveResponse(unsigned long long t, boost::shared_ptr<BaseEvent> event)
	{
		AppConnectorDelegate* delegate = (AppConnectorDelegate*)t;

		boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = event->Params();
		boost::shared_ptr<void> ptrEventParamValueRoom = (*ptrEventParams)["room"];
		boost::shared_ptr<Room> ptrNotifiedRoom = ((boost::static_pointer_cast<Room>)(ptrEventParamValueRoom));

		auto output = new leave_room_output();
		output->_room_name = ptrNotifiedRoom->Name()->c_str();
		delegate->_observer->sendData(output);
	}

CC_CONSTRUCTOR_ACCESS:
	boost::shared_ptr<Sfs2X::SmartFox> _smartFox;
	SmartFoxAppConnector* _observer;
};
//-------------------------------------------------------------------------------
//                                  DELEGATE INPUT
//-------------------------------------------------------------------------------
template<typename T>
class AppBaseDelegateSmartFox : public AppBaseDelegate<T>
{
public:
	AppBaseDelegateSmartFox(boost::shared_ptr<Sfs2X::SmartFox> sf, SmartFoxAppConnector* observer)
	{
		_smartFox = sf;
		_observer = observer;
		Ref::autorelease();
	}

	virtual void process(T* object) = 0;

	boost::shared_ptr<Sfs2X::SmartFox> _smartFox;
	SmartFoxAppConnector* _observer;
};

#define CREATE_DELEGATE_SMARTFOX_CONSTRUCTOR(__TYPE__) \
__TYPE__(boost::shared_ptr<Sfs2X::SmartFox> sf, SmartFoxAppConnector* observer) : AppBaseDelegateSmartFox(sf, observer) \
{ \
}

//-------------------------------------------------------------------------------
class ConnectionInputDelegate : public AppBaseDelegateSmartFox<connect_input>
{
public:
	CREATE_DELEGATE_SMARTFOX_CONSTRUCTOR(ConnectionInputDelegate);

	virtual void process(connect_input* object)
	{
		CCLOG("Connecting to smartfox server");
		_smartFox->Connect(app_configuration::__HOST__.c_str(), app_configuration::__SOCKET_PORT_TCP__);
	}
};

class LoginInputDelegate : public AppBaseDelegateSmartFox<login_input>
{
public:
	CREATE_DELEGATE_SMARTFOX_CONSTRUCTOR(LoginInputDelegate);

	virtual void process(login_input* object)
	{
		auto param = SFSObject::NewInstance();
		param->Put(extparamskey::__PASSWORD__, boost::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDataType::SFSDATATYPE_UTF_STRING, boost::shared_ptr<std::string>(new std::string(object->_password)))));
		param->Put(extparamskey::__USER_NAME__, boost::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDataType::SFSDATATYPE_UTF_STRING, boost::shared_ptr<std::string>(new std::string(object->_username)))));
		/* param->Put(extparamskey::__PASSWORD__, boost::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDataType::SFSDATATYPE_UTF_STRING, boost::shared_ptr<std::string>(new std::string(object->_password)))));
		param->Put(extparamskey::__TYPE__, boost::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDataType::SFSDATATYPE_INT, boost::shared_ptr<long>(new long(object->_type)))));
		param->Put(extparamskey::__PARTNER_ID__, boost::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDataType::SFSDATATYPE_INT, boost::shared_ptr<long>(new long(object->_partner_id)))));
		param->Put(extparamskey::__REF_CODE__, boost::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDataType::SFSDATATYPE_UTF_STRING, boost::shared_ptr<std::string>(new std::string(object->_ref_code)))));
		param->Put(extparamskey::__VERSION_CODE__, boost::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDataType::SFSDATATYPE_UTF_STRING, boost::shared_ptr<std::string>(new std::string(object->_version_code)))));
		param->Put(extparamskey::__IMEI__, boost::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDataType::SFSDATATYPE_UTF_STRING, boost::shared_ptr<std::string>(new std::string(object->_imei)))));*/

		_smartFox->Send(boost::shared_ptr<IRequest>(new LoginRequest(object->_username, object->_password, app_configuration::__ZONE_GAME__, param)));
	}
};

class LogoutInputDelegate : public AppBaseDelegateSmartFox<log_out_input>
{
public:
	CREATE_DELEGATE_SMARTFOX_CONSTRUCTOR(LogoutInputDelegate);

	virtual void process(log_out_input* object)
	{
		_smartFox->Send(boost::shared_ptr<IRequest>(new LogoutRequest()));
	}
};
class JoinRoomInputDelegate : public AppBaseDelegateSmartFox<join_room_input>
{
public:
	CREATE_DELEGATE_SMARTFOX_CONSTRUCTOR(JoinRoomInputDelegate);

	virtual void process(join_room_input* object)
	{
		_smartFox->Send(boost::shared_ptr<IRequest>(new JoinRoomRequest(object->_room_name, object->_password)));
	}
};

class PingPongInputDelegate : public AppBaseDelegateSmartFox<ping_pong_input>
{
public:
	CREATE_DELEGATE_SMARTFOX_CONSTRUCTOR(PingPongInputDelegate);

	virtual void process(ping_pong_input* object)
	{
		if (config::__ENABLE_LAG_TIME_MONITOR__) {
			_smartFox->EnableLagMonitor(object->_enable, object->_time, object->_packs);
		}			
	}
};

class LeaveRoomInputDelegate : public AppBaseDelegateSmartFox<leave_room_input>
{
public:
	CREATE_DELEGATE_SMARTFOX_CONSTRUCTOR(LeaveRoomInputDelegate);

	virtual void process(leave_room_input* object)
	{
		_smartFox->Send(boost::shared_ptr<IRequest>(new LeaveRoomRequest()));
	}
};

class DisconnectInputDelegate : public AppBaseDelegateSmartFox<disconnect_input>
{
public:
	CREATE_DELEGATE_SMARTFOX_CONSTRUCTOR(DisconnectInputDelegate);

	virtual void process(disconnect_input* object)
	{
		_smartFox->Disconnect();
	}
};

class ExtensionInputDelegate : public AppBaseDelegateSmartFox<extension_data>
{
public:
	CREATE_DELEGATE_SMARTFOX_CONSTRUCTOR(ExtensionInputDelegate);

	virtual void process(extension_data* object)
	{
		auto param = SFSObject::NewInstance();
		for (auto it = object->_object._map->begin(); it != object->_object._map->end(); it++)
		{
			std::shared_ptr<connection_data_wrapper> wrapper = std::shared_ptr<connection_data_wrapper>(it->second);
			if (wrapper->isBool())
			{
				param->Put(it->first, boost::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDataType::SFSDATATYPE_BOOL, boost::shared_ptr<bool>(new bool(*std::static_pointer_cast<bool>(wrapper->data))))));
			}
			else if (wrapper->isInt())
			{
				param->Put(it->first, boost::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDataType::SFSDATATYPE_INT, boost::shared_ptr<long int>(new long int(*std::static_pointer_cast<long int>(wrapper->data))))));
			}
			else if (wrapper->isShort())
			{
				param->Put(it->first, boost::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDataType::SFSDATATYPE_SHORT, boost::shared_ptr<short int>(new short int(*std::static_pointer_cast<short int>(wrapper->data))))));
			}
			else if (wrapper->isByte())
			{
				param->Put(it->first, boost::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDataType::SFSDATATYPE_BYTE, boost::shared_ptr<unsigned char>(new unsigned char(*std::static_pointer_cast<unsigned char>(wrapper->data))))));
			}
			else if (wrapper->isLong())
			{
				param->Put(it->first, boost::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDataType::SFSDATATYPE_LONG, boost::shared_ptr<long long>(new long long(*std::static_pointer_cast<long long>(wrapper->data))))));
			}
			else if (wrapper->isDouble())
			{
				param->Put(it->first, boost::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDataType::SFSDATATYPE_DOUBLE, boost::shared_ptr<double>(new double(*std::static_pointer_cast<double>(wrapper->data))))));
			}
			else if (wrapper->isFloat())
			{
				param->Put(it->first, boost::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDataType::SFSDATATYPE_FLOAT, boost::shared_ptr<float>(new float(*std::static_pointer_cast<float>(wrapper->data))))));
			}
			else if (wrapper->isString())
			{
				param->Put(it->first, boost::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDataType::SFSDATATYPE_UTF_STRING, boost::shared_ptr<std::string>(new std::string(*std::static_pointer_cast<std::string>(wrapper->data))))));
			}
			else if (wrapper->isIntArray())
			{
				param->Put(it->first, boost::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDataType::SFSDATATYPE_INT_ARRAY, boost::shared_ptr<std::vector<long int>>(new std::vector<long int>(*std::static_pointer_cast<std::vector<long int>>(wrapper->data))))));
			}
			else if (wrapper->isBoolArray())
			{
				param->Put(it->first, boost::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDataType::SFSDATATYPE_BOOL_ARRAY, boost::shared_ptr<std::vector<bool>>(new std::vector<bool>(*std::static_pointer_cast<std::vector<bool>>(wrapper->data))))));
			}
			else if (wrapper->isByteArray())
			{
				param->Put(it->first, boost::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDataType::SFSDATATYPE_BYTE_ARRAY, boost::shared_ptr<std::vector<unsigned char>>(new std::vector<unsigned char>(*std::static_pointer_cast<std::vector<unsigned char>>(wrapper->data))))));
			}
			else if (wrapper->isShortArray())
			{
				param->Put(it->first, boost::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDataType::SFSDATATYPE_SHORT_ARRAY, boost::shared_ptr<std::vector<short int>>(new std::vector<short int>(*std::static_pointer_cast<std::vector<short int>>(wrapper->data))))));
			}
			else if (wrapper->isLongArray())
			{
				param->Put(it->first, boost::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDataType::SFSDATATYPE_LONG_ARRAY, boost::shared_ptr<std::vector<long long>>(new std::vector<long long>(*std::static_pointer_cast<std::vector<long long>>(wrapper->data))))));
			}
			else if (wrapper->isDoubleArray())
			{
				param->Put(it->first, boost::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDataType::SFSDATATYPE_DOUBLE_ARRAY, boost::shared_ptr<std::vector<double>>(new std::vector<double>(*std::static_pointer_cast<std::vector<double>>(wrapper->data))))));
			}
			else if (wrapper->isFloatArray())
			{
				param->Put(it->first, boost::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDataType::SFSDATATYPE_FLOAT_ARRAY, boost::shared_ptr<std::vector<float>>(new std::vector<float>(*std::static_pointer_cast<std::vector<float>>(wrapper->data))))));
			}
			else if (wrapper->isStringArray())
			{
				param->Put(it->first, boost::shared_ptr<SFSDataWrapper>(new SFSDataWrapper(SFSDataType::SFSDATATYPE_UTF_STRING_ARRAY, boost::shared_ptr<std::vector<std::string>>(new std::vector<std::string>(*std::static_pointer_cast<std::vector<std::string>>(wrapper->data))))));
			}
		}



		if (object->_sendRoom)
		{
			AppConnectorUserRoom* riderroom = (AppConnectorUserRoom*)_observer->_refMap.at((int)AppConnectorEnum::__USER_ROOM__);
			_smartFox->Send(boost::shared_ptr<IRequest>(new ExtensionRequest(object->_cmd, param, riderroom->_room)));
			if (config::__DEBUG_REQUEST__) {
				CCLOG("================ Send Room %s ====================",riderroom->_room->Name()->c_str());
				CCLOG("CMD : %s", object->_cmd.c_str());
				CCLOG("Param : %s", (*param->GetDump()).c_str());
				CCLOG("===============================================");
			}
		}
		else
		{
			_smartFox->Send(boost::shared_ptr<IRequest>(new ExtensionRequest(object->_cmd, param)));
			if (config::__DEBUG_REQUEST__) {
				CCLOG("================ Send Zone ====================");
				CCLOG("CMD : %s", object->_cmd.c_str());
				CCLOG("Param : %s", (*param->GetDump()).c_str());
				CCLOG("===============================================");
			}
		}

	}
};

//-------------------------------------------------------------------------------
//                                  MAIN
//-------------------------------------------------------------------------------
SmartFoxAppConnector::SmartFoxAppConnector() : _connector(nullptr), _timeout(0)
{

}

SmartFoxAppConnector::~SmartFoxAppConnector()
{
	if (_connector)
	{
		delete (SmartFox*)_connector;
		_connector = nullptr;
	}
}

bool SmartFoxAppConnector::init()
{
	_connector = new SmartFox(true);

	auto sfs = boost::shared_ptr<Sfs2X::SmartFox>((SmartFox*)_connector);
	sfs->ThreadSafeMode(true);

	auto roomdata = AppConnectorUserRoom::create(nullptr);
	_refMap.insert((int)AppConnectorEnum::__USER_ROOM__, roomdata);

	auto delegate = AppConnectorDelegate::create(sfs, this);
	_refMap.insert((int)AppConnectorEnum::__APP_CONNECTOR_DELEGATE__, delegate);
	sfs->AddEventListener(SFSEvent::UDP_INIT, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(AppConnectorDelegate::onUDPInit, (unsigned long long)this)));
	sfs->AddEventListener(SFSEvent::CONNECTION, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(AppConnectorDelegate::onConnection, (unsigned long long)delegate)));
	sfs->AddEventListener(SFSEvent::CONNECTION_LOST, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(AppConnectorDelegate::onConnectionLost, (unsigned long long)delegate)));
	sfs->AddEventListener(SFSEvent::CONNECTION_RESUME, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(AppConnectorDelegate::onConnectionResume, (unsigned long long)delegate)));
	sfs->AddEventListener(SFSEvent::CONNECTION_RETRY, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(AppConnectorDelegate::onConnectionRetry, (unsigned long long)delegate)));
	sfs->AddEventListener(SFSEvent::LOGIN, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(AppConnectorDelegate::onLogin, (unsigned long long)delegate)));
	sfs->AddEventListener(SFSEvent::LOGIN_ERROR, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(AppConnectorDelegate::onLoginError, (unsigned long long)delegate)));
	sfs->AddEventListener(SFSEvent::EXTENSION_RESPONSE, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(AppConnectorDelegate::onExtensionResponse, (unsigned long long)delegate)));
	sfs->AddEventListener(SFSEvent::ROOM_JOIN, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(AppConnectorDelegate::onRoomJoinResponse, (unsigned long long)delegate)));
	sfs->AddEventListener(SFSEvent::USER_EXIT_ROOM, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(AppConnectorDelegate::onRoomLeaveResponse, (unsigned long long)delegate)));
	sfs->AddEventListener(SFSEvent::LOGOUT, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(AppConnectorDelegate::onLogout, (unsigned long long)delegate)));
	sfs->AddEventListener(SFSEvent::PING_PONG, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(AppConnectorDelegate::onPingPong, (unsigned long long)delegate)));

	/*                      input delegates                     */
	_apiDelegates.insert(connect_input()._id, (AppBaseDelegate<network_data>*)new ConnectionInputDelegate(sfs, this));
	_apiDelegates.insert(login_input()._id, (AppBaseDelegate<network_data>*)new LoginInputDelegate(sfs, this));
	_apiDelegates.insert(log_out_input()._id, (AppBaseDelegate<network_data>*)new LogoutInputDelegate(sfs, this));
	_apiDelegates.insert(join_room_input()._id, (AppBaseDelegate<network_data>*)new JoinRoomInputDelegate(sfs, this));
	_apiDelegates.insert(leave_room_input()._id, (AppBaseDelegate<network_data>*)new LeaveRoomInputDelegate(sfs, this));
	_apiDelegates.insert(disconnect_input()._id, (AppBaseDelegate<network_data>*)new DisconnectInputDelegate(sfs, this));
	_apiDelegates.insert(extension_data()._id, (AppBaseDelegate<network_data>*)new ExtensionInputDelegate(sfs, this));
	_apiDelegates.insert(ping_pong_input()._id, (AppBaseDelegate<network_data>*)new PingPongInputDelegate(sfs, this));



	ctpl::thread_pool* pool = new ctpl::thread_pool(1);
	pool->push([this](int threadID)
	{
		while (true)
		{
			this->update(0);
			std::this_thread::sleep_for(std::chrono::milliseconds(16));
			std::this_thread::yield();
		}
	});
	return true;
}

void SmartFoxAppConnector::updateServerConfig()
{

}

void SmartFoxAppConnector::update(float delta)
{
	SmartFox* _smartFox = (SmartFox*)_connector;
	_smartFox->ProcessEvents();
	//    if (!_smartFox->IsConnected() && !_smartFox->IsConnecting())
	//    {
	//        auto output = new connect_output();
	//        output->_result = app_string::__LOST__;
	//        sendData(output);
	//    }
	//    else if (!_smartFox->IsConnected() && _smartFox->IsConnecting())
	//    {
	//        _timeout += delta;
	//        if (_timeout >= 5)
	//        {
	//            _smartFox->Disconnect();
	//            _smartFox->SetReconnectionSeconds(5);
	//            _timeout = 0;
	//        }
	//    }
}
void SmartFoxAppConnector::sendData(cocos2d::Ref* ref, bool release)
{
	Director::getInstance()->getScheduler()->performFunctionInCocosThread([ref, release, this]() {
		Observer::sendData(ref, release);
	});
}

void SmartFoxAppConnector::listen(Observer*, cocos2d::Ref* ref)
{
	if (!config::__SMARTFOX_ENABLE__) return;
	auto rdata = dynamic_cast<network_data*>(ref);
	if (rdata)
	{
		auto delegate = _apiDelegates.at(rdata->_id);
		if (delegate)
		{
			delegate->process(rdata);
		}
	}
	
}

bool SmartFoxAppConnector::isUdp()
{
	return ((SmartFox*)_connector)->UdpInited();
}