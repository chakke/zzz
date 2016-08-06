#include "PlayerManager.hpp"

PlayerManager::PlayerManager() {}

PlayerManager* playerManagerInstance = nullptr;
PlayerManager* PlayerManager::getInstance() {
	if (!playerManagerInstance) playerManagerInstance = new PlayerManager();
	return playerManagerInstance;
}

struct compare_int {

	inline bool operator() (int num1, int num2)
	{
		return (num1 < num2);
	}
};

void PlayerManager::addPlayer(std::shared_ptr<connection_object> data) {
	int playerID = data->getInt("id");
	_players.insert(std::make_pair(playerID, new Player(playerID, data)));


	_ids.clear();
	for (auto p : _players) {
		_ids.push_back(p.first);
	}
	std::sort(_ids.begin(), _ids.end(), compare_int());
}
void PlayerManager::removePlayer(std::shared_ptr<connection_object> data) {
	int playerID = data->getInt("id");
	if (_players.find(playerID) != _players.end()) _players.erase(playerID);
}

void PlayerManager::resetAll() {
	_players.clear();
	_ids.clear();
}


Player* PlayerManager::getPlayer(int playerID) {
	if (_players.find(playerID) != _players.end()) {
		return _players.at(playerID);
	}
	return nullptr;
}
std::map<int, Player*> PlayerManager::getPlayers() {
	return _players;
}

int PlayerManager::getPlayerType(int playerID) {
	for (int i = 0; i < _ids.size(); i++) {
		if (_ids.at(i) == playerID) {	
			return i;
		}
	}	
	return 0;
}