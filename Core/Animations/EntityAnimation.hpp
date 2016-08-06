#pragma once

#include "cocos2d.h"

class EntityAnimation{

public:	
	EntityAnimation();
	~EntityAnimation();
	virtual void animate(int name) = 0;
	virtual void setup(int playSide, int entityType, cocos2d::Node* parent) = 0;	
	virtual int getCurrentAnimation();
	virtual bool needSetup();
	virtual void setFlip(bool flip);
protected : 
	int mCurrentAnimation;
	int mSetup;
};
