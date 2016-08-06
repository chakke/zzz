#include "GameConfig.hpp"
#include "../Core/PlayerManager.hpp"
#include "../Config/GameConstants.hpp"
namespace game {
	game::Config* config = nullptr;

	void setupConfig() {
		config = new Config();
	}
	Config::Config() :mWorldWidth(4000), mWorldHeight(2400), mViewportWidth(1920), mViewportHeight(1080), mPlayerID(-1), mBlockInput(true), mMapType(3), mPlaySide(game::side::SIDE_1),mUniqueID(0) {}
	void Config::setGameConfig(std::shared_ptr<connection_object> data) {	
		this->mGameConfig = data;
	}
	
	int Config::getType(int playerID) {

		return PlayerManager::getInstance()->getPlayerType(playerID);
	}
	int Config::getMapType() {
		return mMapType;
	}

	void Config::setMapType(int type) {
		this->mMapType = type;
	}

	int Config::getPlaySide(int index) {
		return this->mPlaySide + index;
	}
	void Config::setPlaySide(int playSide) {
		this->mPlaySide = playSide;
	}

	void Config::setEnemySide(int playSide) {
		this->mEnemySide = playSide;
	}
	int Config::getEnenySide(const int index) {
		return this->mEnemySide + index;
	}

	bool Config::isBlockInput(){
		return mBlockInput;
	}
	void Config::setBlockInput(bool block) {
		mBlockInput = block;
	}
	int Config::getWorldWidth()
	{
		return mWorldWidth;
	}
	int Config::getWorldHeight()
	{
		return mWorldHeight;
	}

	int Config::getViewportWidth()
	{
		return mViewportWidth;
	}
	int Config::getViewportHeight()
	{
		return mViewportHeight;
	}
	int Config::getPlayerID()
	{
		return mPlayerID;
	}
	int Config::getPlayerIDDefault()
	{
		return -1;
	}


	cocos2d::Size Config::getWorldSize()
	{
		return cocos2d::Size(mWorldWidth, mWorldHeight);
	}
	cocos2d::Size Config::getViewportSize()
	{
		return cocos2d::Size(mViewportWidth,mViewportHeight);
	}

	Config * Config::setWorldHeight(int height)
	{
		this->mWorldHeight = height;
		return this;
	}
	Config * Config::setWorldWidth(int width)
	{
		this->mWorldWidth = width;
		return this;
	}

	Config * Config::setViewportHeight(int height)
	{
		this->mViewportHeight = height;
		return this;
	}
	Config * Config::setViewportWidth(int width)
	{
		this->mViewportWidth = width;
		return this;
	}

	Config * Config::setPlayerID(int id)
	{
		this->mPlayerID = id;
		return this;
	}
	int Config::getUniqueID() {
		return mUniqueID++;
	}
	
};

