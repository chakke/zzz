#pragma once
#include "cocos2d.h"
#include "../../Data/ConnectionData.hpp"
#include "CommandObserver.hpp"
/*
Written by Badlogic
Arcade Dota
20-04-2016
*/

class CommandDispatcher {
public:
	static CommandDispatcher* getInstance();
	virtual std::shared_ptr<connection_object> dispatchForResult(int commandTag, std::shared_ptr<connection_object> data = nullptr);
	virtual void dispatch(int commandTag,std::shared_ptr<connection_object> data = nullptr);
	virtual void dispatch(int observerID,int commandTag, std::shared_ptr<connection_object> data);
	virtual void registerObserver(CommandObserver* observer);
	virtual void unRegisterObserver(int observerID);
	virtual void unRegisterAll();

protected:
	std::map<int, CommandObserver*> _listeners;

private :
	CommandDispatcher();
	
};
