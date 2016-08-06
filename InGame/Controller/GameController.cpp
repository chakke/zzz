
#include "GameController.hpp"
#include "../../UIParser/UIParser.hpp"
#include "../../Network/AppConnectorBuilder.hpp"
#include "../../Game/Controller/ChoiceRoomController.hpp"
#include "../../Utils/Functions.hpp"
#include "../../Network/AppConnectorConfig.hpp"
#include "../../UIParser/CustomUI/CustomUIData.h"
#include "../../Game/GameModel/Cache.hpp"
#include "../../Network/AppConnectorConfig.hpp"
#include "../../Game/Controller/ToastController.hpp"
#include "../../Game/Controller/LevelsController.hpp"
#include "../../Game/Controller/ConnectionController.hpp"
#include "../../Data/AppString.hpp"
#include "../../Config/Config.hpp"

#include "../../Core/Command/CommandDispatcher.hpp"
#include "../../Core/Command/Commands.hpp"

#include "../../Demo/Demos.hpp"

#include "../../ECS/GameConfig.hpp"
#include "../../Game/Controller/LoginController.hpp"
#include "PrepareMatchController.hpp"
#include "PingController.hpp"
#include "HudController.hpp"




namespace game {

	void closeGame(GameController* GameController) {
		auto controller = GameController->getParent();
		if (controller) {
			app_function::destroyTree(GameController->getView());
			GameController->getView()->removeFromParent();
			controller->removeSubController(GameController, true);

			auto nextController = LevelsController::create();
			controller->addSubController(nextController);
			controller->getView()->addChild(nextController->getView());

			UIParser::refreshAllViewConstraint(2);
			game_model::__user_cache__->_joined_room_name = "";
			game::config->setPlayerID(game::config->getPlayerIDDefault());
		}
	}

}


bool GameController::init()
{
	auto node = UIParser::parse("xml/game/mainGame.xml");
	setView(node);

	auto rootParser = (UIParser*)dynamic_cast<CustomUIData*>(node)->getCustomUIData().at(0);

	//============== add subs controller ==============
	

	CommandDispatcher::getInstance()->unRegisterAll();

	{
		mHudController = HudController::create();
		addSubController(mHudController);
		mHudController->setBackCallback(CC_CALLBACK_0(GameController::onTouchBack, this));
		getView()->addChild(mHudController->getView());
		CommandDispatcher::getInstance()->registerObserver(mHudController);
	}
	
	{
		auto rootNode = rootParser->getHasNodes()->at("root");
		mGame = new ArriveDemo();
		mGame->initGameLayout(game::config->getWorldSize(), rootNode);
		mGame->createWorld();
	}
	
	getView()->runAction(cocos2d::Sequence::createWithTwoActions(cocos2d::DelayTime::create(1), cocos2d::CallFunc::create([=]() {
		CommandDispatcher::getInstance()->dispatch(command::ON_ANIMATION_NEW_MATCH);
	})));
	
	return true;
}

void GameController::onRemove()
{
	unscheduleUpdate();
	AppConnectorBuilder::getInstance()->removeDestination(this);
	removeDestination(AppConnectorBuilder::getInstance());
}

void GameController::onLinked()
{
	scheduleUpdate();
	AppConnectorBuilder::getInstance()->addDestination(this);
	addDestination(AppConnectorBuilder::getInstance());

}

void GameController::update(float delta)
{
	mGame->process(delta);
}

void GameController::listen(Observer * sender, cocos2d::Ref * ref)
{

	auto data = dynamic_cast<extension_data*>(ref);
	if (data) {
		const auto& it = _cmd_delegates.find(data->_cmd);
		if (it != _cmd_delegates.end())
		{
			it->second(data->_object);
		}
	}
}

void GameController::onTouchBack()
{
	game::closeGame(this);
	CCLOG("Touch back");
}
