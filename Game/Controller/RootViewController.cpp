
#include "RootViewController.hpp"

#include "../../Utils/Functions.hpp"
#include "../../Network/AppConnectorBuilder.hpp"
#include "../../Data/ObserverData.hpp"
#include "../../Data/AppString.hpp"
#include "../../Game/GameModel/Cache.hpp"
#include "../../UIParser/UIParser.hpp"
#include "../../UIParser/CustomUI/CustomUIData.h"
#include "../../Utils/Functions.hpp"
#include "../../Utils/Log.h"
#include "ConnectionController.hpp"
#include "LoginController.hpp"
#include "LoadingViewController.hpp"
#include "LevelsController.hpp"
#include "ChoiceRoomController.hpp"

#include "../../InGame/Controller/DemoController.hpp"
#include "../../Config/Config.hpp"
#include "../../Network/AppConnectorConfig.hpp"
USING_NS_CC;
namespace root_view
{
	void on_choiced_room(join_room_output* data, RootViewController* controller) {
		CCLOG("on Joined room %s", data->_notity_room_name.c_str());

		for (Controller* sub : controller->getSubControllers())
		{
			auto choiceRoomController = dynamic_cast<ChoiceRoomController*>(sub);
			if (choiceRoomController) {
				game_model::__user_cache__->_joined_room_id = choiceRoomController->_joined_table->_room_id;
				game_model::__user_cache__->_joined_room_name = choiceRoomController->_joined_table->_room_name;
				app_function::destroyTree(choiceRoomController->getView());
				choiceRoomController->getView()->removeFromParent();
				controller->removeSubController(choiceRoomController, true);


				//auto nextController = InGameController::create();
				//controller->addSubController(nextController);
				//controller->getView()->addChild(nextController->getView());


				UIParser::refreshAllViewConstraint(2);
				break;
			}
		}
	}

	void on_leave_room(extension_data* data, RootViewController* controller) {
		//CCLOG("on leave room %s", data->_room_name.c_str());

		for (Controller* sub : controller->getSubControllers())
		{
		/*	auto inGameController = dynamic_cast<InGameController*>(sub);
			if (inGameController) {
				app_function::destroyTree(inGameController->getView());
				inGameController->getView()->removeFromParent();
				controller->removeSubController(inGameController, true);

				auto nextController = ChoiceRoomController::create();
				controller->addSubController(nextController);
				controller->getView()->addChild(nextController->getView());

				UIParser::refreshAllViewConstraint(2);
				break;
			}*/
		}
		game_model::__user_cache__->_joined_room_name = "";
		game_model::__user_cache__->_joined_room_id = -1;
	}

	void on_loading_finish(RootViewController* controller)
	{
		CCLOG("on loading view success");
		for (Controller* sub : controller->getSubControllers())
		{
			auto loadingController = dynamic_cast<LoadingViewController*>(sub);
			if (loadingController) {
				app_function::destroyTree(loadingController->getView());
				loadingController->getView()->removeFromParent();
				controller->removeSubController(loadingController, true);

				if (config::__TEST_DEMO__) {
					auto nextController = DemoController::create();
					controller->addSubController(nextController);
					controller->getView()->addChild(nextController->getView());
				}
				else {
					auto nextController = LevelsController::create();
					controller->addSubController(nextController);
					controller->getView()->addChild(nextController->getView());
				}
				
				/*}else {
					auto nextController = LoginController::create();
					controller->addSubController(nextController);
					controller->getView()->addChild(nextController->getView());
				}*/

				UIParser::refreshAllViewConstraint(2);
				break;
			}
		}
	}

	void on_login_callback(const std::string& result, RootViewController* controller)
	{
		if (result.compare(app_string::__SUCCESS__) == 0 && !game_model::__user_cache__->_account.empty()) // login game successfully
		{
			// FIRST : REMOVE LOGIN CONTROLLER
			// SECOND : ADD CHOICE ROOM CONTROLLER
			for (Controller* sub : controller->getSubControllers())
			{
				auto loginController = dynamic_cast<LoginController*>(sub);
				if (loginController) {
					app_function::destroyTree(loginController->getView());
					loginController->getView()->removeFromParent();
					controller->removeSubController(loginController, true);

					auto nextController = ChoiceRoomController::create();
					controller->addSubController(nextController);
					controller->getView()->addChild(nextController->getView());


					UIParser::refreshAllViewConstraint(2);
					break;
				}
			}


		}
	}

	void on_maintainance_callback(RootViewController* controller)
	{
		//FIXME
	}
};

bool RootViewController::init()
{
	AppConnectorBuilder::getInstance(); // init app connector

	auto node = UIParser::parse("xml/root.xml");
	setView(node);


	auto connectionController = ConnectionController::getInstance();
	addSubController(connectionController);
	connectionController->setLoginCallback(std::bind(root_view::on_login_callback, std::placeholders::_1, this));
	connectionController->setMaintainanceCallback(std::bind(root_view::on_maintainance_callback, this));

	auto loadingController = LoadingViewController::create();
	addSubController(loadingController);
	getView()->addChild(loadingController->getView());
	loadingController->setOnLoadingViewCallback(std::bind(root_view::on_loading_finish, this));

	return true;
}

void RootViewController::update(float delta)
{
}

void RootViewController::onRemove()
{
	unscheduleUpdate();
	AppConnectorBuilder::getInstance()->removeDestination(this);
	removeDestination(AppConnectorBuilder::getInstance());
}

void RootViewController::onLinked()
{
	scheduleUpdate();
	AppConnectorBuilder::getInstance()->addDestination(this);
	addDestination(AppConnectorBuilder::getInstance());
}

void RootViewController::listen(Observer* sender, cocos2d::Ref* ref)
{


	{
		auto data = dynamic_cast<join_room_output*>(ref);
		if (data)
		{
			CCLOG("on join room output");
			root_view::on_choiced_room(data, this);
		}
	}

	//{
	//	auto data = dynamic_cast<extension_data*>(ref);
	//	if (data && data->_cmd.compare(cmd::__PLAYER_LEAVER__) != 0)
	//	{
	//		CCLOG("on join room output");
	//		root_view::on_leave_room(data, this);
	//	}
	//}
}