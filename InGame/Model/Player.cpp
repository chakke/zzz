#include "Player.hpp"

Player::Player() {
	mPlayerID = -1;
	mData = nullptr;
}


Player::Player(int playerID, std::shared_ptr<connection_object> data) {
	mPlayerID = playerID;
	mData = data;
}

int Player::getPlayerID() {
	return mPlayerID;
}
std::string Player::getPlayerName() {
	if (mData) return *mData->getString("name");
	return "No name";
}

std::shared_ptr<connection_object> Player::getPlayerData() {
	return mData;
}
std::shared_ptr<connection_object>  Player::onMessage(int type, std::shared_ptr<connection_object> data) {
	return nullptr;
}