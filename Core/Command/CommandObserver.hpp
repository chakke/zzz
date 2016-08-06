#pragma once
#include "cocos2d.h"
#include "../../Data/ConnectionData.hpp"

/*
Written by Badlogic
Arcade Dota
20-04-2016
*/

class CommandObserver {
public:
	CommandObserver();
	~CommandObserver();
	virtual std::shared_ptr<connection_object> onMessage(int commandTag, std::shared_ptr<connection_object> data);
	virtual void onRecieveCommand(int commandTag,std::shared_ptr<connection_object> data);
	virtual void sendCommand(int tag, std::shared_ptr<connection_object> data = nullptr);
	virtual void setObservable(bool observable);
	virtual bool isObservable();
	virtual int getObserverID();
	virtual void setObserverID(int id);
	virtual void registerCommand(int commandTag,const std::function<void(std::shared_ptr<connection_object>)> &function);
	virtual void removeCommand(int commandTag);
	virtual void unRegisterAllCommand();
protected:
	bool mObservable;
	int mObserverID;
	std::unordered_map<int, std::function<void(std::shared_ptr<connection_object>)>> _delegates;
};
 