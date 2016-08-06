#pragma once

#include "../../AppController/Controller.hpp"
#include "../../UIParser/UIParser.hpp"
#include "../../Data/ConnectionData.hpp"
class ResultMatchController : public Controller
{
public:
	CREATE_FUNC(ResultMatchController);

    virtual bool init();
    
    virtual void onRemove();
    
    virtual void onLinked();
    
    virtual void update(float delta);
    
    virtual void listen(Observer* sender, cocos2d::Ref* ref);
	
	void showResultMatch(std::shared_ptr<connection_object> data);
	void showResultMatch(bool isWin);
private :
	void onTouchMenu(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void onTouchReplay(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void onTouchPlay(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	void onNewMatch(connection_object object);
	void onResetMatch(connection_object object);
	void onFinishMatch(connection_object object);

	
	std::unordered_map<std::string, std::function<void(connection_object)>> _cmd_delegates;

	UIParser* mRootParser;	
};


