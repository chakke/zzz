
#include "PrepareMatchController.hpp"
#include "../../Network/AppConnectorBuilder.hpp"
#include "../../UIParser/CustomUI/CustomUIData.h"
#include "../../UIParser/CustomUI/CustomUIRichText.h"
#include "../../Game/GameModel/Cache.hpp"
#include "../../Config/Config.hpp"
#include "../../Network/AppConnectorConfig.hpp"
bool PrepareMatchController::init()
{
	auto node = UIParser::parse("xml/game/prepare_match.xml");
	setView(node);
	mRootParser = (UIParser*)dynamic_cast<CustomUIData*>(node)->getCustomUIData().at(0);


	_cmd_delegates.insert(std::make_pair(cmd::__PREPARE_MATCH__, CC_CALLBACK_1(PrepareMatchController::onPrepareMatch, this)));
	_cmd_delegates.insert(std::make_pair(cmd::__NEW_MATCH__, CC_CALLBACK_1(PrepareMatchController::onNewMatch, this)));
	_cmd_delegates.insert(std::make_pair(cmd::__RESET_MATCH__, CC_CALLBACK_1(PrepareMatchController::onFinishMatch, this)));
	_cmd_delegates.insert(std::make_pair(cmd::__FINISH_MATCH__, CC_CALLBACK_1(PrepareMatchController::onResetMatch, this)));


	mTextTime = cocos2d::ui::Text::create("", "fonts/SF-UI-Display-Semibold.otf", 60);
	mTextTime->setTextColor(cocos2d::Color4B::WHITE);
	mTextTime->setAnchorPoint(cocos2d::Vec2(.5f, .5f));
	mTextTime->setCascadeOpacityEnabled(true);
	mRootParser->getHasNodes()->at("root")->addChild(mTextTime);

	mTime = new TimeComponent();
	mTime->setActive(false);
	mTime->setMaxTime(5000);
	mTime->setCurrentTime(5000);
	node->setVisible(false);
	return true;
}

void PrepareMatchController::onRemove()
{
	unscheduleUpdate();
	AppConnectorBuilder::getInstance()->removeDestination(this);
	removeDestination(AppConnectorBuilder::getInstance());
}

void PrepareMatchController::onLinked()
{
	scheduleUpdate();
	AppConnectorBuilder::getInstance()->addDestination(this);
	addDestination(AppConnectorBuilder::getInstance());
}

void PrepareMatchController::update(float delta)
{
	if (mTime->isActive()) {
		mTime->setCurrentTime(mTime->getCurrentTime() - delta * 1000);
		if (mTime->getCurrentTime() < 0) mTime->setCurrentTime(0);
		int current = (int)(mTime->getCurrentTime());
		int second = current / 1000;
		mTextTime->setString(cocos2d::StringUtils::format("%d", second + 1).c_str());
	}

}
void PrepareMatchController::onNewMatch(connection_object object)
{
	mTime->setActive(false);
	getView()->setVisible(false);
}
void PrepareMatchController::onPrepareMatch(connection_object object)
{
	mTime->setActive(true);
	int time = object.getInt(extparamskey::TIME);
	mTime->setMaxTime(time);
	mTime->setCurrentTime(time);
	getView()->setVisible(true);
	int second = time / 1000;
	mTextTime->setString(cocos2d::StringUtils::format("%d", second + 1).c_str());
	this->update(0);
}
void PrepareMatchController::onResetMatch(connection_object object)
{
	mTime->setActive(false);
	getView()->setVisible(false);
}
void PrepareMatchController::onFinishMatch(connection_object object)
{
	mTime->setActive(false);
	getView()->setVisible(false);
}
void PrepareMatchController::listen(Observer* sender, cocos2d::Ref* ref) {

	auto data = dynamic_cast<extension_data*>(ref);
	if (data) {
		const auto& it = _cmd_delegates.find(data->_cmd);
		if (it != _cmd_delegates.end())
		{
			it->second(data->_object);
		}
	}
}