#pragma once

#include "cocos2d.h"
#include "EntityAnimation.hpp"

class SpriteAnimation : public EntityAnimation {

public:

	SpriteAnimation();
	~SpriteAnimation();

	void animate(int name);
	void animate(int name, bool loop);
	void setup(int playSide, int entityType, cocos2d::Node* parent);
	int getCurrentAnimation();
	bool needSetup();
	void setFlip(bool flip);

protected:
	virtual int getAnimationName(int animation);
	virtual bool checkLoop(int name);
	cocos2d::Sprite* mSprite;
	int mPlaySide;
	int mEntityType;
};
