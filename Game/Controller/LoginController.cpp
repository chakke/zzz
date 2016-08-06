#include "LoginController.hpp"
#include "../../UIParser/CustomUI/CustomUIData.h"
#include "../../Network/AppConnectorBuilder.hpp"
#include "../../UIParser/CustomUI/CustomUIEditBox.hpp"
#include "../../Utils/Functions.hpp"
#include "../../Data/AppString.hpp"
#include "ConnectionController.hpp"
#include "ToastController.hpp"
#include "Utils/Log.h"
#include "../../Network/AppConnectorConfig.hpp"
#include "../GameModel/Cache.hpp"
#include "../../UIParser/CustomUI/CustomUIEditBox.hpp"
#include "../../UIParser/CustomUI/CustomUIImageView.hpp"
#include "../../UIParser/Atlas/AtlasCache.hpp"
#include "../../Config/Config.hpp"
#include "../../Data/AppConfiguration.hpp"
namespace login_view
{

	void on_register_callback(const std::string& result, LoginController* controller)
	{
		auto customUIData = dynamic_cast<CustomUIData*>(controller->getView());
		auto rootParser = (UIParser*)customUIData->getCustomUIData().at(0);
		rootParser->getHasNodes()->at("message_connecting")->setVisible(false);

		if (result.compare(app_string::__SUCCESS__) == 0)
		{
			ToastController::getInstance()->toast(app_string::getValueMap("strings/login.plist")->at("REGISTER_SUCCESS").asString(), 2.0);
		}
		else {
			ToastController::getInstance()->toast(result.c_str(), 4.0);
		}
	}

};

bool LoginController::init()
{
	auto node = UIParser::parse("xml/login.xml");
	setView(node);

	auto customUIData = dynamic_cast<CustomUIData*>(node);

	rootParser = (UIParser*)customUIData->getCustomUIData().at(0);

	rootParser->getTouchDelegates()->at("touch_login")->setDelegate(CC_CALLBACK_2(LoginController::onLoginClick, this));
	rootParser->getTouchDelegates()->at("touch_register")->setDelegate(CC_CALLBACK_2(LoginController::onRegisterClick, this));
	rootParser->getTouchDelegates()->at("touch_btn_login")->setDelegate(CC_CALLBACK_2(LoginController::onLoginClick, this));
	rootParser->getTouchDelegates()->at("touch_btn_register")->setDelegate(CC_CALLBACK_2(LoginController::onRegisterClick, this));
	rootParser->getTouchDelegates()->at("touch_remember")->setDelegate(CC_CALLBACK_2(LoginController::onRememberPasswordClick, this));
	//rootParser->getTouchDelegates()->at("touch_local")->setDelegate(CC_CALLBACK_2(LoginController::onSelectLocalServer, this));
	//rootParser->getTouchDelegates()->at("touch_online")->setDelegate(CC_CALLBACK_2(LoginController::onSelectOnlineServer, this));
	rootParser->getTouchDelegates()->at("touch_back")->setDelegate(CC_CALLBACK_2(LoginController::onTouchBack, this));
	ConnectionController::getInstance()->setRegisterCallback(std::bind(login_view::on_register_callback, std::placeholders::_1, this));

	// load previous username and password
	if (game_model::__user_cache__->_account.compare("") != 0) {
		auto editBox = dynamic_cast<CustomUIEditBox*>(rootParser->getHasNodes()->at("username"));
		if (editBox) {
			editBox->setText(game_model::__user_cache__->_account.c_str());
		}
		if (game_model::__user_cache__->_remember_password) {
			auto editBoxPass = dynamic_cast<CustomUIEditBox*>(rootParser->getHasNodes()->at("password"));
			if (editBoxPass) {
				editBoxPass->setText(game_model::__user_cache__->_password.c_str());
			}
		}
		else {
			auto customImageView = dynamic_cast<CustomUIImageView*>(rootParser->getHasNodes()->at("remember"));
			if (customImageView) {
				customImageView->setSpriteFrame(atlas_cache::getSpriteFrame("atlas/login.plist", "remember_off.png"));
			}
		}
	}

	auto btnLocal = dynamic_cast<CustomUIImageView*>(rootParser->getHasNodes()->at("btn_local"));
	auto btnOnline = dynamic_cast<CustomUIImageView*>(rootParser->getHasNodes()->at("btn_online"));
	if (btnLocal && btnOnline) {
		btnLocal->setSpriteFrame(atlas_cache::getSpriteFrame("atlas/login.plist", !config::__USE_ONLINE_SERVER__ ? "remember_on.png" : "remember_off.png"));
		btnOnline->setSpriteFrame(atlas_cache::getSpriteFrame("atlas/login.plist", config::__USE_ONLINE_SERVER__ ? "remember_on.png" : "remember_off.png"));
	}

	{
		background = cocos2d::ui::ImageView::create("texture/login.png");
		auto visibleSize = cocos2d::Director::getInstance()->getWinSize();
		background->setAnchorPoint(cocos2d::Vec2(.5f,.5f));
		background->setScaleX(visibleSize.width/background->getContentSize().width);
		background->setScaleY(visibleSize.height/background->getContentSize().height);
		background->setScale9Enabled(true);
		rootParser->getHasNodes()->at("layout_background")->addChild(background);
	}

	STATE_NONE = 0;
	STATE_LOGIN = 1;
	STATE_REGISTER = 2;
	mState = -1;
	setState(STATE_NONE);

	rootParser->getHasNodes()->at("img_remember")->setVisible(game_model::__user_cache__->_remember_password);
	return true;
}

void LoginController::onRemove()
{
	this->unscheduleUpdate();
	AppConnectorBuilder::getInstance()->removeDestination(this);
	removeDestination(AppConnectorBuilder::getInstance());
}

void LoginController::onLinked()
{
	this->scheduleUpdate();
	AppConnectorBuilder::getInstance()->addDestination(this);
	addDestination(AppConnectorBuilder::getInstance());
}

void LoginController::update(float delta)
{
}

void LoginController::listen(Observer * sender, cocos2d::Ref * ref)
{
	auto connectOutPut = dynamic_cast<connect_output*>(ref);
	if (connectOutPut) {
		rootParser->getHasNodes()->at("message_connecting")->setVisible(false);

	}


	auto data = dynamic_cast<login_output*>(ref);
	if (data)
	{
		if (data->_result.compare(app_string::__FAIL__) == 0)
		{
			if (data->_message.empty())
			{
				ToastController::getInstance()->toast(app_string::getValueMap("strings/login.plist")->at("LOGIN_FAILED").asString(), 2.0);
			}
			else
			{
				ToastController::getInstance()->toast(data->_message, 2.0);
			}
		}
	}

}

void LoginController::onLoginClick(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {		
		CCLOG("touch login");
		if (mState == STATE_LOGIN) {
			auto parser = (UIParser*)dynamic_cast<CustomUIData*>(_view)->getCustomUIData().at(0);
			auto username = dynamic_cast<CustomUIEditBox*>(parser->getHasNodes()->at("username"));
			auto password = dynamic_cast<CustomUIEditBox*>(parser->getHasNodes()->at("password"));


			std::string name = username->getText();
			std::string pw = password->getText();

			name = app_function::trim(name);
			pw = app_function::trim(pw);

			if (name.empty() && pw.empty())
			{
				ToastController::getInstance()->toast(app_string::getValueMap("strings/login.plist")->at("EMPTY_ALL").asString(), 2.0);
				return;
			}

			if (name.empty())
			{
				ToastController::getInstance()->toast(app_string::getValueMap("strings/login.plist")->at("WRONG_ACCOUNT").asString(), 2.0);
				return;
			}

			if (pw.empty())
			{
				ToastController::getInstance()->toast(app_string::getValueMap("strings/login.plist")->at("WRONG_PASSWORD").asString(), 2.0);
				return;
			}

			ConnectionController::getInstance()->login(game_model::__USER__, name, pw);
			parser->getHasNodes()->at("message_connecting")->setVisible(true);
		}
		else {		
			setState(STATE_LOGIN);
		}
	}
}

void LoginController::onRegisterClick(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		CCLOG("click to register");

		if (mState == STATE_REGISTER) {
			auto parser = (UIParser*)dynamic_cast<CustomUIData*>(_view)->getCustomUIData().at(0);
			auto username = dynamic_cast<CustomUIEditBox*>(parser->getHasNodes()->at("username"));
			auto password = dynamic_cast<CustomUIEditBox*>(parser->getHasNodes()->at("password"));


			std::string name = username->getText();
			std::string pw = password->getText();

			name = app_function::trim(name);
			pw = app_function::trim(pw);

			if (name.empty() && pw.empty())
			{
				ToastController::getInstance()->toast(app_string::getValueMap("strings/login.plist")->at("EMPTY_ALL").asString(), 2.0);
				return;
			}

			if (name.empty())
			{
				ToastController::getInstance()->toast(app_string::getValueMap("strings/login.plist")->at("WRONG_ACCOUNT").asString(), 2.0);
				return;
			}

			if (pw.empty())
			{
				ToastController::getInstance()->toast(app_string::getValueMap("strings/login.plist")->at("WRONG_PASSWORD").asString(), 2.0);
				return;
			}
			parser->getHasNodes()->at("message_connecting")->setVisible(true);
			ConnectionController::getInstance()->registerAccount(name, pw);
		}
		else {
			setState(STATE_REGISTER);		
		}
	}
}
void LoginController::onRememberPasswordClick(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		game_model::__user_cache__->_remember_password = !game_model::__user_cache__->_remember_password;
		auto node = rootParser->getHasNodes()->at("img_remember");
		node->setVisible(game_model::__user_cache__->_remember_password);
		CCLOG("xxxx");
	}
}

void LoginController::onSelectLocalServer(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		config::__USE_ONLINE_SERVER__ = !config::__USE_ONLINE_SERVER__;
		auto btnLocal = dynamic_cast<CustomUIImageView*>(rootParser->getHasNodes()->at("btn_local"));
		auto btnOnline = dynamic_cast<CustomUIImageView*>(rootParser->getHasNodes()->at("btn_online"));
		if (btnLocal && btnOnline) {
			btnLocal->setSpriteFrame(atlas_cache::getSpriteFrame("atlas/login.plist", !config::__USE_ONLINE_SERVER__ ? "remember_on.png" : "remember_off.png"));
			btnOnline->setSpriteFrame(atlas_cache::getSpriteFrame("atlas/login.plist", config::__USE_ONLINE_SERVER__ ? "remember_on.png" : "remember_off.png"));
		}
		app_configuration::setupServer();
	}
}

void LoginController::onSelectOnlineServer(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		config::__USE_ONLINE_SERVER__ = !config::__USE_ONLINE_SERVER__;
		auto btnLocal = dynamic_cast<CustomUIImageView*>(rootParser->getHasNodes()->at("btn_local"));
		auto btnOnline = dynamic_cast<CustomUIImageView*>(rootParser->getHasNodes()->at("btn_online"));
		if (btnLocal && btnOnline) {
			btnLocal->setSpriteFrame(atlas_cache::getSpriteFrame("atlas/login.plist", !config::__USE_ONLINE_SERVER__ ? "remember_on.png" : "remember_off.png"));
			btnOnline->setSpriteFrame(atlas_cache::getSpriteFrame("atlas/login.plist", config::__USE_ONLINE_SERVER__ ? "remember_on.png" : "remember_off.png"));
		}
		app_configuration::setupServer();
	}

}

void LoginController::onTouchBack(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		setState(STATE_NONE);
		CCLOG("on click back");
	}	
}

void LoginController::showLoginPage()
{
	background->loadTexture("texture/background_login.png");
	rootParser->getHasNodes()->at("layout_btns")->setVisible(false);
	rootParser->getHasNodes()->at("layout_logins")->setVisible(true);
	rootParser->getHasNodes()->at("btn_login")->setVisible(true);
	rootParser->getHasNodes()->at("btn_register")->setVisible(false);
	rootParser->getHasNodes()->at("back")->setVisible(true);
}

void LoginController::showRegisterPage()
{
	background->loadTexture("texture/background_login.png");
	rootParser->getHasNodes()->at("layout_btns")->setVisible(false);
	rootParser->getHasNodes()->at("layout_logins")->setVisible(true);
	rootParser->getHasNodes()->at("btn_login")->setVisible(false);
	rootParser->getHasNodes()->at("btn_register")->setVisible(true);
	rootParser->getHasNodes()->at("back")->setVisible(true);
}

void LoginController::showFlashPage()
{
	background->loadTexture("texture/login.png");
	rootParser->getHasNodes()->at("layout_btns")->setVisible(true);
	rootParser->getHasNodes()->at("layout_logins")->setVisible(false);
	rootParser->getHasNodes()->at("back")->setVisible(false);
}

void LoginController::setState(int newState)
{
	if (mState == newState) return;
	mState = newState;
	if (mState == STATE_NONE) {
		showFlashPage();
	}

	if (mState == STATE_LOGIN) {
		showLoginPage();
	}
	if (mState == STATE_REGISTER) {
		showRegisterPage();
	}
}
