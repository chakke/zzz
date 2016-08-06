#pragma once
#include "../../AppController/Controller.hpp"
#include "../../Data/ConnectionData.hpp"
#include "../../Core/AbstractGame.hpp"
#include "../../UIParser/UIParser.hpp"
class DemoController : public Controller
{
public:
    CREATE_FUNC(DemoController);

    virtual bool init();
    
    virtual void onRemove();
    
    virtual void onLinked();
    
    virtual void update(float delta);

	virtual void listen(Observer* sender, cocos2d::Ref* ref);

private :
	virtual void setGame(AbstractGame* game,const std::string &title);	
	virtual void addTestCase(std::string name,const std::function<void(std::string)> &callback);
	virtual void closeDemo();
	AbstractGame*	mMainGame;
	UIParser*		mRootParser;
};

