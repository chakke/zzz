#pragma once
#include "../../AppController/Controller.hpp"
#include "../../UIParser/UIParser.hpp"
#include "ui/CocosGUI.h"
#include "../../Data/ConnectionData.hpp"
#include "../../ECS/Component/TimeComponent.hpp"
class PrepareMatchController : public Controller
{
public:
    CREATE_FUNC(PrepareMatchController);
    
    virtual bool init();
    
    virtual void onRemove();
    
    virtual void onLinked();
    
    virtual void update(float delta);

private :
	UIParser* mRootParser;
	void onNewMatch(connection_object object);
	void onPrepareMatch(connection_object object);
	void onResetMatch(connection_object object);
	void onFinishMatch(connection_object object);
	
	virtual void listen(Observer* sender, cocos2d::Ref* ref);
	std::unordered_map<std::string, std::function<void(connection_object)>> _cmd_delegates;
	
	TimeComponent* mTime;
	cocos2d::ui::Text* mTextTime;
	cocos2d::ui::Text* mLabelTime;
};
