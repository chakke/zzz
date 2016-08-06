#pragma once
#include "cocos2d.h"
#include "../../Data/ConnectionData.hpp"

class Player {
public:
	Player();
	Player(int playerID, std::shared_ptr<connection_object> data);
	virtual int getPlayerID();
	virtual std::string getPlayerName();
	virtual std::shared_ptr<connection_object> getPlayerData();
	virtual std::shared_ptr<connection_object> onMessage(int type, std::shared_ptr<connection_object> data);
protected :
	int mPlayerID;
	std::shared_ptr<connection_object> mData;
};



