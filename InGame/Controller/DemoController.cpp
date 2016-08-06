
#include "DemoController.hpp"
#include "../../UIParser/UIParser.hpp"
#include "../../Network/AppConnectorBuilder.hpp"
#include "../../Network/AppConnectorConfig.hpp"
#include "../../UIParser/CustomUI/CustomUIData.h"
#include "../../UIParser/CustomUI/CustomUIListView.hpp"
#include "../../UIParser/CustomUI/CustomUIRichText.h"
#include "../../Core/Command/CommandDispatcher.hpp"
#include "../../Core/Command/Commands.hpp"
#include "../../ECS/GameConfig.hpp"
#include "../../Demo/Demos.hpp"
bool DemoController::init()
{
	auto node = UIParser::parse("xml/demo/demo.xml");
	setView(node);

	mRootParser = (UIParser*)dynamic_cast<CustomUIData*>(node)->getCustomUIData().at(0);
	mRootParser->getTouchDelegates()->at("touch_back")->setDelegate([=](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED) closeDemo();
	});

	mRootParser->getHasNodes()->at("title")->setVisible(false);
	mRootParser->getHasNodes()->at("back")->setVisible(false);

	addTestCase("ARRIVE Demo", [=](std::string name) {
		this->setGame(new ArriveDemo(),name);
	});
	addTestCase("ATTACK Demo", [=](std::string name) {
		this->setGame(new AttackDemo(), name);
	});
	addTestCase("AUTO ATTACK Demo", [=](std::string name) {
		this->setGame(new AutoAttackDemo(), name);
	});
	addTestCase("MOVEMENT Demo", [=](std::string name) {
		this->setGame(new MovementDemo(), name);
	});
	return true;
}

void DemoController::onRemove()
{
	unscheduleUpdate();
	AppConnectorBuilder::getInstance()->removeDestination(this);
	removeDestination(AppConnectorBuilder::getInstance());
}

void DemoController::onLinked()
{
	scheduleUpdate();
	AppConnectorBuilder::getInstance()->addDestination(this);
	addDestination(AppConnectorBuilder::getInstance());

}

void DemoController::update(float delta)
{
	if (mMainGame) mMainGame->process(delta);
}

void DemoController::listen(Observer * sender, cocos2d::Ref * ref)
{
}

void DemoController::setGame(AbstractGame * game, const std::string & title)
{
	if (mMainGame) mMainGame->onRemoved();
	mMainGame = game;
	game->onAdded();
	game->initGameLayout(game::config->getWorldSize(),mRootParser->getHasNodes()->at("root"));
	game->createWorld();

	mRootParser->getHasNodes()->at("title")->setVisible(true);
	mRootParser->getHasNodes()->at("back")->setVisible(true);
	mRootParser->getHasNodes()->at("listview")->setVisible(false);
	

	auto titleNode = dynamic_cast<CustomRichText*>(mRootParser->getHasNodes()->at("title"));
	titleNode->getRichElement<CustomRichElementText*>(0)->_text =title;
	titleNode->updateText();
}


void DemoController::addTestCase(std::string name, const std::function<void(std::string)>& callback)
{
	auto listview = dynamic_cast<CustomUIListView*>(mRootParser->getHasNodes()->at("listview"));
	if (listview) {
		//listview->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
		auto itemLayout = cocos2d::ui::Layout::create();
		itemLayout->setLayoutType(cocos2d::ui::Layout::Type::RELATIVE);
		auto text = cocos2d::ui::Text::create(name, "fonts/SF-UI-Text-Light.oft", 30);
		auto rp = cocos2d::ui::RelativeLayoutParameter::create();
		rp->setAlign(cocos2d::ui::RelativeLayoutParameter::RelativeAlign::CENTER_IN_PARENT);
		text->setLayoutParameter(rp->clone());
		itemLayout->setContentSize(cocos2d::Size(listview->getContentSize().width, text->getContentSize().height + 20));
		itemLayout->addChild(text);

		itemLayout->setTouchEnabled(true);
		itemLayout->addClickEventListener([=](cocos2d::Ref* sender) {
			if (callback) callback(name);
		});

		itemLayout->setLayoutParameter(rp->clone());

		listview->pushBackCustomItem(itemLayout);
	}
}

void DemoController::closeDemo()
{
	mRootParser->getHasNodes()->at("title")->setVisible(false);
	mRootParser->getHasNodes()->at("back")->setVisible(false);
	if (mMainGame) { 
		mMainGame->onRemoved(); 
	}
	mRootParser->getHasNodes()->at("listview")->setVisible(true);
}
