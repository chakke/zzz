#pragma once
#include "cocos2d.h"
#include "../../AppController/Controller.hpp"
#include "ui/CocosGUI.h"
#include "../../UIParser/UIParser.hpp"

class LoginController : public Controller
{
public:
    CREATE_FUNC(LoginController);
    
    virtual bool init();
    
    virtual void onRemove();
    
    virtual void onLinked();
    
    virtual void update(float delta);
    
    virtual void listen(Observer* sender, cocos2d::Ref* ref);

	void onLoginClick(cocos2d::Ref* sender,cocos2d::ui::Widget::TouchEventType type);
	void onRegisterClick(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void onRememberPasswordClick(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void onSelectLocalServer(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void onSelectOnlineServer(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void onTouchBack(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
private :
	void showLoginPage();
	void showRegisterPage();
	void showFlashPage();
	void setState(int newState);
	
	int mState;
	int STATE_NONE;
	int STATE_LOGIN;
	int STATE_REGISTER;

	UIParser* rootParser;
	cocos2d::ui::ImageView* background;
};

