
#include "ResultMatchController.hpp"

#include "../../UIParser/CustomUI/CustomUIData.h"
#include "../../Network/AppConnectorBuilder.hpp"
#include "../../Network/AppConnectorConfig.hpp"
#include "../../Game/Controller/ChoiceRoomController.hpp"
bool ResultMatchController::init()
{	
	auto node = UIParser::parse("xml/game/result_match_controller.xml");
	setView(node);

	mRootParser = (UIParser*)dynamic_cast<CustomUIData*>(node)->getCustomUIData().at(0);
	mRootParser->getTouchDelegates()->at("touch_menu")->setDelegate(CC_CALLBACK_2(ResultMatchController::onTouchMenu, this));
	mRootParser->getTouchDelegates()->at("touch_replay")->setDelegate(CC_CALLBACK_2(ResultMatchController::onTouchReplay, this));
	mRootParser->getTouchDelegates()->at("touch_play")->setDelegate(CC_CALLBACK_2(ResultMatchController::onTouchPlay, this));

	_cmd_delegates.insert(std::make_pair(cmd::__NEW_MATCH__, CC_CALLBACK_1(ResultMatchController::onNewMatch, this)));
	_cmd_delegates.insert(std::make_pair(cmd::__RESET_MATCH__, CC_CALLBACK_1(ResultMatchController::onResetMatch, this)));
	_cmd_delegates.insert(std::make_pair(cmd::__FINISH_MATCH__, CC_CALLBACK_1(ResultMatchController::onFinishMatch, this)));

	return true;
}

void ResultMatchController::onRemove()
{
	this->unscheduleUpdate();
	AppConnectorBuilder::getInstance()->removeDestination(this);
	removeDestination(AppConnectorBuilder::getInstance());
}

void ResultMatchController::onLinked()
{
	this->scheduleUpdate();
	AppConnectorBuilder::getInstance()->addDestination(this);
	addDestination(AppConnectorBuilder::getInstance());
}


void ResultMatchController::update(float delta)
{

}

void ResultMatchController::listen(Observer* sender, cocos2d::Ref* ref)
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

void ResultMatchController::onTouchMenu(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	
	/*
	getView()->removeFromParent();
	removeSelf(true);*/
	
}

void ResultMatchController::onTouchReplay(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	
	auto parent = getParent();
	for (auto c : parent->getSubControllers()) {
		
	}

	getView()->removeFromParent();
	removeSelf(true);
}

void ResultMatchController::onTouchPlay(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	
	/*getView()->removeFromParent();
	removeSelf(true);*/

}

void ResultMatchController::onNewMatch(connection_object object)
{
	CCLOG("=====================================");
	CCLOG("new match");
}

void ResultMatchController::onResetMatch(connection_object object)
{
	CCLOG("reset match");
	auto dt = std::shared_ptr<connection_object>(new connection_object());
	dt->putBool("result",true);
	dt->putString("message", "Nguời chơi thoát bất thường.");
	showResultMatch(dt);
}

void ResultMatchController::onFinishMatch(connection_object object)
{
	CCLOG("finish match");
	auto dt = std::shared_ptr<connection_object>(new connection_object());
	dt->putBool("result", true);	
	showResultMatch(dt);
}

void ResultMatchController::showResultMatch(std::shared_ptr<connection_object> data)
{
	bool isWin = data->getBool("result");
	if (isWin) {
		for (int i = 1; i < 4; i++)
		{
			auto star = mRootParser->getHasNodes()->at(cocos2d::StringUtils::format("star_%d",i).c_str());
			star->setVisible(true);
		}
	
		mRootParser->getHasNodes()->at("background_win")->setVisible(true);
		mRootParser->getHasNodes()->at("victory")->setVisible(true);

		mRootParser->getHasNodes()->at("background_win")->setVisible(false);
		mRootParser->getHasNodes()->at("victory")->setVisible(false);
	}
	else {
		for (int i = 1; i < 4; i++)
		{
			auto star = mRootParser->getHasNodes()->at(cocos2d::StringUtils::format("star_%d", i).c_str());
			star->setVisible(false);
		}
		mRootParser->getHasNodes()->at("background_win")->setVisible(false);
		mRootParser->getHasNodes()->at("victory")->setVisible(false);

		mRootParser->getHasNodes()->at("background_win")->setVisible(true);
		mRootParser->getHasNodes()->at("victory")->setVisible(true);	
	}
}

void ResultMatchController::showResultMatch(bool isWin)
{

	auto board = mRootParser->getHasNodes()->at("board");
	board->setVisible(false);
	float dst = 800;
	board->setPositionX(board->getPositionX()+ dst);
	board->runAction(cocos2d::Sequence::create(cocos2d::MoveBy::create(0, cocos2d::Vec2(dst, 0)), cocos2d::CallFunc::create([=]() {
		board->setVisible(true);
	}), cocos2d::MoveBy::create(.2f, cocos2d::Vec2(-dst, 0)), nullptr));

	if (isWin) {
		for (int i = 1; i < 4; i++)
		{
			auto star = mRootParser->getHasNodes()->at(cocos2d::StringUtils::format("star_%d", i).c_str());
			star->setVisible(true);
			star->setScale(0);
			star->runAction(cocos2d::Sequence::create(cocos2d::DelayTime::create(.4f + i*.1f), cocos2d::ScaleTo::create(.2f,1),nullptr));
		}

		mRootParser->getHasNodes()->at("background_win")->setVisible(true);
		auto title = mRootParser->getHasNodes()->at("victory");
		title->setVisible(true);
		title->setScale(0);
		title->runAction(cocos2d::Sequence::create(cocos2d::DelayTime::create(.1), cocos2d::ScaleTo::create(.2f, 1), nullptr));


		mRootParser->getHasNodes()->at("background_lose")->setVisible(false);
		mRootParser->getHasNodes()->at("defeat")->setVisible(false);


	}
	else {
		for (int i = 1; i < 4; i++)
		{
			auto star = mRootParser->getHasNodes()->at(cocos2d::StringUtils::format("star_%d", i).c_str());
			star->setVisible(false);
		}
		mRootParser->getHasNodes()->at("background_win")->setVisible(false);
		mRootParser->getHasNodes()->at("victory")->setVisible(false);

		mRootParser->getHasNodes()->at("background_lose")->setVisible(true);		
		auto title = mRootParser->getHasNodes()->at("defeat");
		title->setVisible(true);
		title->setScale(0);
		title->runAction(cocos2d::Sequence::create(cocos2d::DelayTime::create(.1f), cocos2d::ScaleTo::create(.2f, 1), nullptr));
	}
}
