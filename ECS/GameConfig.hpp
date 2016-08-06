#pragma once
#include "cocos2d.h"
#include "../Utils/Direction.h"
#include "../Data/ConnectionData.hpp"
namespace game
{
	class Config {
	public :		
		Config();
		Config* setPlayerID(int id);

		int getWorldWidth();
		int getWorldHeight();
		int getViewportWidth();
		int getViewportHeight();
		cocos2d::Size getWorldSize();
		cocos2d::Size getViewportSize();

		Config* setWorldHeight(int height);
		Config* setWorldWidth(int width);
		Config* setViewportHeight(int height);
		Config* setViewportWidth(int width);


		bool isBlockInput();
		void setBlockInput(bool block);

		int getPlayerID();
		int getPlayerIDDefault();				
		int getType(int playerID);


		int getMapType();
		void setMapType(int type);

		void setPlaySide(int playSide);
		int getPlaySide(const int index = 0);
		void setEnemySide(int playSide);
		int getEnenySide(const int index = 0);

		int getUniqueID();

		void setGameConfig(std::shared_ptr<connection_object> data);		
	protected:

		int mWorldWidth;
		int mWorldHeight;
		int mViewportWidth;
		int mViewportHeight;
		int mPlayerID;
		int mPlaySide;
		int mEnemySide;
		/*
		default : 1
		1 : nen dat
		2 : nen co
		3 : nen tuyet
		*/
		int mMapType;
		bool mBlockInput;
		int mUniqueID;

		std::shared_ptr<connection_object> mGameConfig;
		
	};

	extern game::Config* config;
	void setupConfig();
};


