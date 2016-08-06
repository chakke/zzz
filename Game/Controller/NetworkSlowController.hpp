#pragma once
#include "../../AppController/Controller.hpp"
#include "../../UIParser/UIParser.hpp"
#include "../../Data/ConnectionData.hpp"
class NetworkSlowController : public Controller
{
public:
    CREATE_FUNC(NetworkSlowController);
    
    virtual bool init();
    
    virtual void onRemove();
    
    virtual void onLinked();
    
    virtual void update(float delta);
    
	virtual void showNetworkSlow(bool networkSlow);

	virtual void listen(Observer* sender, cocos2d::Ref* ref);

	
private:
	void updateTextLoading();
	void onUpdateStates(connection_object object);
	void onFinishMatch(connection_object object);
	void onNewMatch(connection_object object);
	void onResetMatch(connection_object object);
	
	UIParser* mRootParser;
	long long mLastTime;
	long long mWaitTime;
	long long mLoadingTime;
	int mCountResponse;
	std::vector<std::shared_ptr<connection_object>> responseDelay;
	std::unordered_map<std::string, std::function<void(connection_object)>> _cmd_delegates;

};
