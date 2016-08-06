#pragma once
#include "cocos2d.h"
namespace game
{
	
	
	class GameAnimations {
	public:
		static GameAnimations* getInstance();
		void loadAnimations();
		void releaseAllAnimations();
		cocos2d::Animation* getAnimation(int name);
		
	private:
		GameAnimations();		
		bool loadAnimation(int playerType, int entity_type, int animation);
		std::map<int, cocos2d::Animation*> _animations;
	};
};


