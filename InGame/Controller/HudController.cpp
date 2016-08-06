
#include "HudController.hpp"
#include "../../UIParser/UIParser.hpp"
#include "../../UIParser/CustomUI/CustomUIData.h"
#include "../../UIParser/CustomUI/CustomLabelBMF.hpp"
#include "../../UIParser/CustomUI/CustomUIImageView.hpp"
#include "../../Network/AppConnectorBuilder.hpp"
#include "../../ECS/GameConfig.hpp"
#include "../../Config/GameConstants.hpp"
#include "../../UIParser/Atlas/AtlasCache.hpp"
#include "../../Network/AppConnectorConfig.hpp"
#include "../../Core/Command/CommandDispatcher.hpp"
#include "../../Core/Command/Commands.hpp"
#include "../../Core/PlayerManager.hpp"
#include "spine/spine-cocos2dx.h"
bool HudController::init()
{	
	auto node = UIParser::parse("xml/game/hud.xml");
	setView(node);

	mRootParser = (UIParser*)dynamic_cast<CustomUIData*>(node)->getCustomUIData().at(0);
	mRootParser->getTouchDelegates()->at("touchback")->setDelegate(CC_CALLBACK_2(HudController::onTouchBack, this));
	mRootParser->getTouchDelegates()->at("touch_builder")->setDelegate(CC_CALLBACK_2(HudController::onTouchBuilder, this));
	mRootParser->getTouchDelegates()->at("touch_babarian")->setDelegate(CC_CALLBACK_2(HudController::onTouchBabarian, this));
	mRootParser->getTouchDelegates()->at("touch_horse")->setDelegate(CC_CALLBACK_2(HudController::onTouchHorse, this));
	mRootParser->getTouchDelegates()->at("touch_archer")->setDelegate(CC_CALLBACK_2(HudController::onTouchArcher, this));

	{
		auto layoutInput = dynamic_cast<cocos2d::ui::Layout*>(mRootParser->getHasNodes()->at("layout_capacity"));
		layoutInput->setTouchEnabled(true);
		layoutInput->addTouchEventListener([=](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type) {

			if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
				auto pos = layoutInput->getTouchBeganPosition();
				pos = layoutInput->convertToNodeSpace(pos);
				setPercent(pos.y / layoutInput->getContentSize().height, true);
			}

			if (type == cocos2d::ui::Widget::TouchEventType::MOVED) {
				auto pos = layoutInput->getTouchMovePosition();
				pos = layoutInput->convertToNodeSpace(pos);
				setPercent(pos.y / layoutInput->getContentSize().height, true);

			}
			if (type == cocos2d::ui::Widget::TouchEventType::ENDED || type == cocos2d::ui::Widget::TouchEventType::CANCELED) {
				if (getPercent() < .25f) setPercent(0);
				else if (getPercent() > .75f) setPercent(1);
				else setPercent(.5f);
			}
		});

		ninepatch = cocos2d::ui::ImageView::create("texture/nine_patch_2.png");
		ninepatch->setAnchorPoint(cocos2d::Vec2(.5, 0));
		ninepatch->setScale9Enabled(true);
		ninepatch->setCapInsets(cocos2d::Rect(0, 20, 41, 46));
		ninepatch->setPosition(cocos2d::Vec2(layoutInput->getContentSize().width / 2, 20));
		layoutInput->addChild(ninepatch);
	}


	{
		// change content
		auto listview = mRootParser->getHasNodes()->at("listview");
		listview->removeAllChildren();
		addBuilder(game::troop::BABARIAN);
		addBuilder(game::troop::HORSE);
		addBuilder(game::troop::FORTRESS);
		addBuilder(game::troop::ARCHER, false, true);
	}
	_troops.push_back(true);
	_troops.push_back(true);
	_troops.push_back(true);

	mRanger = hudcontroller::Ranger();


	mCastleID = -1;
	setPercent(1);
	setTroopEnable(game::troop::BABARIAN, true);
	setTroopEnable(game::troop::HORSE, true);
	setTroopEnable(game::troop::ARCHER, true);

	
	
	return true;
}

void HudController::onRemove()
{
	this->unscheduleUpdate();
	AppConnectorBuilder::getInstance()->removeDestination(this);
	removeDestination(AppConnectorBuilder::getInstance());
}

void HudController::onLinked()
{
	this->scheduleUpdate();
	AppConnectorBuilder::getInstance()->addDestination(this);
	addDestination(AppConnectorBuilder::getInstance());
}


void HudController::update(float delta)
{
	float dt = mRanger.mValue - mRanger.mCurrent;
	if (dt != 0)
	{
		if (abs(dt) < .05f) mRanger.mCurrent = mRanger.mValue; else
			mRanger.mCurrent += mRanger.mThreshold*dt;
		updateRangerUI();
	}
}

void HudController::listen(Observer* sender, cocos2d::Ref* ref)
{

}

void HudController::onRecieveCommand(int commandTag, std::shared_ptr<connection_object> data)
{
	if (commandTag == command::ON_NEW_MATCH) {
		{
			// change content
			updateUINewMatch();

		}
	}
	else if (commandTag == command::ON_ANIMATION_NEW_MATCH) {

		showLayoutBuilders(false, true);
		mRanger.mCurrent = mRanger.mMin;
		setPercent(mRanger.mMax);
		mCastleID = -1;
		mRootParser->getHasNodes()->at("troop_capacity")->setVisible(true);
		mRootParser->getHasNodes()->at("layout_troops")->setVisible(true);


		setTroopEnable(game::troop::BABARIAN, true);
		setTroopEnable(game::troop::HORSE, true);
		setTroopEnable(game::troop::ARCHER, true);

		{
			for (int i = 0; i < 3; i++) {
				auto btnTroop = mRootParser->getHasNodes()->at(cocos2d::StringUtils::format("btn_troop_%d", i));
				btnTroop->setCascadeOpacityEnabled(true);
				btnTroop->setOpacity(0);
				btnTroop->runAction(cocos2d::Sequence::createWithTwoActions(cocos2d::DelayTime::create(.4f + .2f*i), cocos2d::FadeIn::create(.2f)));
			}
		}

		{
			auto node = mRootParser->getHasNodes()->at("layout_players");
			node->setVisible(true);
			node->stopAllActions();
			node->setPositionY(node->getPositionY() + 100);
			node->runAction(cocos2d::MoveTo::create(.2f, cocos2d::Vec2(node->getPositionX(), node->getPositionY() - 100)));
		}

		{
			auto node = mRootParser->getHasNodes()->at("layout_battle");			
			auto skeleton = spine::SkeletonAnimation::createWithFile("spine/sword.json", "spine/sword.atlas");
			skeleton->setAnimation(0, "sword_fight", false);
			skeleton->setPosition(cocos2d::Size(node->getContentSize().width / 2, node->getContentSize().height / 2 ));
			skeleton->setScale(1.2f);
			node->addChild(skeleton);		
		}

	}
	else	if (commandTag == command::ON_FINISH_MATCH) {
		showLayoutBuilders(false);
		mRootParser->getHasNodes()->at("layout_troops")->setVisible(false);
		mRootParser->getHasNodes()->at("layout_players")->setVisible(false);
		mRootParser->getHasNodes()->at("troop_capacity")->setVisible(false);
	}
	else if (commandTag == command::ON_RESET_MATCH) {
		showLayoutBuilders(false);
		mRootParser->getHasNodes()->at("layout_troops")->setVisible(false);
		mRootParser->getHasNodes()->at("layout_players")->setVisible(false);
		mRootParser->getHasNodes()->at("troop_capacity")->setVisible(false);

	}
	else if (commandTag == command::INIT_MAP) {
		// update player name
		auto players = PlayerManager::getInstance()->getPlayers();
		for (auto player : players) {
			int type = game::config->getType(player.first);
			std::string key = cocos2d::StringUtils::format("player%d", type + 1);
			auto lbName = dynamic_cast<CustomLabelBMF*> (mRootParser->getHasNodes()->at(key));
			if (lbName) lbName->setString(player.second->getPlayerName());

		}

		showLayoutBuilders(false, true);
		mRootParser->getHasNodes()->at("layout_troops")->setVisible(false);
		mRootParser->getHasNodes()->at("layout_players")->setVisible(false);
		mRootParser->getHasNodes()->at("troop_capacity")->setVisible(false);
	}
	else if (commandTag == command::SHOW_HUD_BUILD_TROOP) {
		showLayoutBuilders(true);
		mCastleID = data->getInt("castle_id");
	}
	else if (commandTag == command::HIDE_HUD_BUILD_TROOP) {
		showLayoutBuilders(false);
		mCastleID = -1;
	}
	else if (commandTag == command::HUD_UPDATE_TROOP) {
		int total = data->getInt("total_troop");
		int capacity = data->getInt("capacity");
		auto txt = dynamic_cast<CustomLabelBMF*>(mRootParser->getHasNodes()->at("troop_capacity"));
		txt->setString(cocos2d::StringUtils::format("%s/%d", cocos2d::StringUtils::format("%d", total).c_str(), capacity).c_str());
	}
	else if (commandTag == command::RESET_HUD_TRANSFER) {
		setPercent(1);
	}
}

std::shared_ptr<connection_object> HudController::onMessage(int commandTag, std::shared_ptr<connection_object> data)
{
	if (commandTag == command::ASK_HUD_TROOP_TRANSFER_CONFIG) {
		auto dt = std::shared_ptr<connection_object>(new connection_object());
		std::vector<long> troops;
		for (int i = 0; i < _troops.size(); i++) {
			troops.push_back(_troops.at(i) ? 1 : 0);
		}
		dt->putFloat("percent", mRanger.mValue);
		dt->putIntArray("troops", troops);
		return dt;
	}
	return nullptr;
}

void HudController::setBackCallback(const std::function<void()>& callback)
{
	this->_back_callback = callback;
}


void HudController::onTouchBack(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		if (_back_callback) _back_callback();
		/*auto data = new extension_data();
		data->_cmd = cmd::__ROOM__ + "." + cmd::__LEAVER_ROOM__;

		auto object = new connection_object();
		data->_object = *object;
		data->_sendRoom = true;
		sendData(data);*/
	}
}

void HudController::onTouchBabarian(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		int type = game::troop::BABARIAN;
		setTroopEnable(type, !_troops.at(type));
	}
}

void HudController::onTouchHorse(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		int type = game::troop::HORSE;
		setTroopEnable(type, !_troops.at(type));
	}
}

void HudController::onTouchArcher(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		int type = game::troop::ARCHER;
		setTroopEnable(type, !_troops.at(type));
	}
}

void HudController::onTouchBuilder(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		auto node = dynamic_cast<cocos2d::Node*>(sender);
		auto data = (hudcontroller::BuilderType*) (node->getUserObject());
		auto dt = std::shared_ptr<connection_object>(new connection_object());
		dt->putInt("castle_id", mCastleID);
		dt->putInt("type", data->mType);
		CommandDispatcher::getInstance()->dispatch(command::ON_CLICK_GENERATE_CASTLE_HOUSE, dt);
	}
}

void HudController::addBuilder(int type, bool isNew, bool isLocked)
{
	auto builderData = new hudcontroller::BuilderType(type, isNew, isLocked);
	builderData->autorelease();
	auto listView = mRootParser->getHasNodes()->at("listview");
	auto xmlnode = mRootParser->getHashXmlNodes()->at("builders");
	auto item = UIParser::parse(xmlnode, mRootParser);
	auto itemparser = (UIParser*)dynamic_cast<CustomUIData*>(item)->getCustomUIData().at(0);
	item->setUserObject(builderData);
	std::string atlas = "atlas/game_ui.plist";
	{

		if (isLocked) {
			auto texture = dynamic_cast<CustomUIImageView*> (itemparser->getHasNodes()->at("builder_texture"));
			texture->setSpriteFrame(atlas_cache::getSpriteFrame(atlas.c_str(), "btn-build-lock.png"));
			itemparser->getHasNodes()->at("layout_new")->setVisible(false);
		}
		else {
			itemparser->getHasNodes()->at("layout_new")->setVisible(isNew);

			int playSide = game::config->getPlaySide();

			std::string builderName = "nhalinh";
			if (type == game::troop::BABARIAN) builderName = "nhalinh";
			if (type == game::troop::HORSE) builderName = "nhangua";
			if (type == game::troop::ARCHER) builderName = "nhacung";
			if (type == game::troop::FORTRESS) builderName = "phaodai";

			auto texture = dynamic_cast<CustomUIImageView*> (itemparser->getHasNodes()->at("builder_texture"));
			texture->setSpriteFrame(atlas_cache::getSpriteFrame("atlas/game_ui.plist", cocos2d::StringUtils::format("%d-btn-%s-up.png", playSide, builderName.c_str()).c_str()));
		}
	}
	(dynamic_cast<cocos2d::ui::Layout*>(item))->setTouchEnabled(!isLocked);
	listView->addChild(item);
}

void HudController::showHud(bool show)
{

}

void HudController::updateUINewMatch()
{
	auto listview = mRootParser->getHasNodes()->at("listview");
	listview->removeAllChildren();
	addBuilder(game::troop::BABARIAN);
	addBuilder(game::troop::HORSE);
	addBuilder(game::troop::FORTRESS);
	addBuilder(game::troop::ARCHER, false, true);

	setTroopEnable(game::troop::BABARIAN, true);
	setTroopEnable(game::troop::HORSE, true);
	setTroopEnable(game::troop::ARCHER, true);

	auto iconRight = dynamic_cast<CustomUIImageView*>(mRootParser->getHasNodes()->at("icon-player-right"));
	auto iconLeft = dynamic_cast<CustomUIImageView*>(mRootParser->getHasNodes()->at("icon-player-left"));

	iconLeft->setSpriteFrame(atlas_cache::getSpriteFrame("atlas/game_ui.plist", cocos2d::StringUtils::format("%d-icon-army.png",game::config->getPlaySide())));
	iconRight->setSpriteFrame(atlas_cache::getSpriteFrame("atlas/game_ui.plist", cocos2d::StringUtils::format("%d-icon-army.png", game::config->getEnenySide())));
	

}

void HudController::showLayoutBuilders(bool show, bool force)
{
	auto node = mRootParser->getHasNodes()->at("layout_builders");
	if (force) {
		node->stopAllActions();
		if (show) node->setPosition(cocos2d::Vec2(0, node->getPositionY())); else node->setPosition(cocos2d::Vec2(-400, node->getPositionY()));
		node->setVisible(show);
	}
	else {
		if (node->getNumberOfRunningActions() == 0) {
			if (show) {
				node->setVisible(true);
				node->runAction(cocos2d::Sequence::create(cocos2d::MoveTo::create(.1f, cocos2d::Vec2(0, node->getPositionY())), cocos2d::CallFunc::create([=]() {
					node->setVisible(show);
				}), nullptr));
			}
			else {
				node->runAction(cocos2d::Sequence::create(cocos2d::MoveTo::create(.1f, cocos2d::Vec2(-400, node->getPositionY())), cocos2d::CallFunc::create([=]() {
					node->setVisible(show);
				}), nullptr));
			}
		}
	}


}

void HudController::setPercent(float percent, bool force)
{
	percent = MAX(percent, 0.16f);
	percent = MIN(percent, 1);
	mRanger.mValue = percent;
	if (force) {
		mRanger.mCurrent = percent;
		updateRangerUI();
	}
}

void HudController::updateRangerUI()
{
	auto pointer = mRootParser->getHasNodes()->at("pointer");
	float height = mRanger.mCurrent * 280;
	pointer->setPositionY(height + pointer->getContentSize().height / 2 - 4);
	ninepatch->setContentSize(cocos2d::Size(ninepatch->getContentSize().width, height));
}

void HudController::setTroopEnable(int type, bool enable)
{
	_troops.at(type) = enable;

	if (!_troops.at(type)) {
		std::string builderName = "btn-linh-up.png";

		if (type == game::troop::BABARIAN) {
			builderName = "btn-linh-up.png";
		}
		else if (type == game::troop::HORSE) {
			builderName = "btn-ngua-up.png";
		}
		else if (type == game::troop::ARCHER) {
			builderName = "btn-cung-up.png";
		}
		auto btn = dynamic_cast<CustomUIImageView*>(mRootParser->getHasNodes()->at(cocos2d::StringUtils::format("btn_troop_%d", type).c_str()));
		btn->setSpriteFrame(atlas_cache::getSpriteFrame("atlas/game_ui.plist", builderName.c_str()));
	}
	else {

		int playSide = game::config->getPlaySide();
		std::string builderName = "linh";
		if (type == game::troop::BABARIAN) { builderName = "linh"; }
		else if (type == game::troop::HORSE) { builderName = "ngua"; }
		else if (type == game::troop::ARCHER) { builderName = "cung"; }

		auto btn = dynamic_cast<CustomUIImageView*>(mRootParser->getHasNodes()->at(cocos2d::StringUtils::format("btn_troop_%d", type).c_str()));
		btn->setSpriteFrame(atlas_cache::getSpriteFrame("atlas/game_ui.plist", cocos2d::StringUtils::format("%d-btn-%s-down.png", playSide, builderName.c_str()).c_str()));
	}
}

float HudController::getPercent()
{
	return mRanger.mValue;
}
