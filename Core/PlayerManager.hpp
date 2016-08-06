#pragma once
#include "cocos2d.h"
#include "../Data/ConnectionData.hpp"
#include "../InGame/Model/Player.hpp"
class PlayerManager {
public:

	static PlayerManager* getInstance();
	virtual void addPlayer(std::shared_ptr<connection_object> data);
	virtual void removePlayer(std::shared_ptr<connection_object> data);	
	virtual int getPlayerType(int playerID);
	virtual Player* getPlayer(int playerID);	
	std::map<int, Player*> getPlayers();
	virtual void resetAll();
private:
	std::map<int, Player*> _players;
	std::vector<int> _ids;
	PlayerManager();
};



