#pragma once
#include "../../AppController/Controller.hpp"
#include "../../Data/ConnectionData.hpp"
#include "../../Core/AbstractGame.hpp"
#include "HudController.hpp"

class GameController: public Controller
{
public:
    CREATE_FUNC(GameController);

    virtual bool init();
    
    virtual void onRemove();
    
    virtual void onLinked();
    
    virtual void update(float delta);

	virtual void listen(Observer* sender, cocos2d::Ref* ref);

private :
	std::unordered_map<std::string, std::function<void(connection_object)>> _cmd_delegates;

	void onTouchBack();	

	AbstractGame* mGame;
	HudController*  mHudController;
};

