#include "LevelsController.hpp"
#include "../../UIParser/UIParser.hpp"
#include "../../Network/AppConnectorBuilder.hpp"
#include "../../UIParser/CustomUI/CustomUIData.h"
#include "../../UIParser/CustomUI/CustomUIListView.hpp"
#include "RootViewController.hpp"
#include "../../Utils/Functions.hpp"
#include "../../InGame/Controller/GameController.hpp"
namespace levels {
	void goToGame(RootViewController* controller) {
		for (Controller* sub : controller->getSubControllers())
		{
			auto currentController = dynamic_cast<LevelsController*>(sub);
			if (currentController) {
				
				app_function::destroyTree(currentController->getView());
				currentController->getView()->removeFromParent();
				controller->removeSubController(currentController, true);

				auto nextController = GameController::create();
				controller->addSubController(nextController);
				controller->getView()->addChild(nextController->getView());


				UIParser::refreshAllViewConstraint(2);
				break;
			}
		}
	}

}

bool LevelsController::init()
{
	auto node = UIParser::parse("xml/levels.xml");
	setView(node);
	auto parser = (UIParser*)dynamic_cast<CustomUIData*>(_view)->getCustomUIData().at(0);
	auto listitem = dynamic_cast<CustomUIListView*> (parser->getHasNodes()->at("listview"));
	listitem->setBounceEnabled(false);
	listitem->removeAllChildren();
	auto xmlnode = parser->getHashXmlNodes()->at("rooms");
	for (int i = 0; i < 12; i += 5)
	{
		auto item = UIParser::parse(xmlnode, parser);
		auto itemparser = (UIParser*)dynamic_cast<CustomUIData*>(item)->getCustomUIData().at(0);
		listitem->addChild(item);
		int index = 0;
		while (index < 5) {
			auto room = itemparser->getHasNodes()->at(cocos2d::StringUtils::format("room_%d", index + 1).c_str());
			room->setVisible(true);
			auto roomParser = (UIParser*)dynamic_cast<CustomUIData*>(room)->getCustomUIData().at(0);
			index++;
		}

		listitem->scrollToBottom(2.0f, true);
		//UIParser::refreshAllViewConstraint(2);
	}

	parser->getTouchDelegates()->at("touch_item")->setDelegate(CC_CALLBACK_2(LevelsController::onTouchLevel,this));
	return true;
}


void LevelsController::onRemove()
{
	AppConnectorBuilder::getInstance()->removeDestination(this);
	removeDestination(AppConnectorBuilder::getInstance());
}

void LevelsController::onLinked()
{
	AppConnectorBuilder::getInstance()->addDestination(this);
	addDestination(AppConnectorBuilder::getInstance());
}

void LevelsController::update(float delta)
{
}

void LevelsController::onTouchLevel(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		CCLOG("touch level");
		levels::goToGame(dynamic_cast<RootViewController*>(getParent()));

	
			/*for (Controller* sub : controller->getSubControllers())
			{
				auto choiceRoomController = dynamic_cast<ChoiceRoomController*>(sub);
				if (choiceRoomController) {
					game_model::__user_cache__->_joined_room_id = choiceRoomController->_joined_table->_room_id;
					game_model::__user_cache__->_joined_room_name = choiceRoomController->_joined_table->_room_name;
					app_function::destroyTree(choiceRoomController->getView());
					choiceRoomController->getView()->removeFromParent();
					controller->removeSubController(choiceRoomController, true);

					auto nextController = InGameController::create();
					controller->addSubController(nextController);
					controller->getView()->addChild(nextController->getView());


					UIParser::refreshAllViewConstraint(2);
					break;
				}
			}*/
		

	}
}

