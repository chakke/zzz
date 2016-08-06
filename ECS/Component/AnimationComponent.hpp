#pragma once

#include "cocos2d.h"
#include "../../artemis/Component.h"
#include "../../Core/Animations/EntityAnimation.hpp"
class AnimationComponent : public artemis::Component {
	
public:	
	AnimationComponent(EntityAnimation* entityAnimation);
	~AnimationComponent();
	virtual int getCurrentAnimation();
	virtual void animate(int name);
	virtual void setup(int playSide, int entityType,cocos2d::Node* parent);
	virtual bool needSetup();
	virtual void setFlip(bool flip);
protected:
	EntityAnimation* mAnimation;
};
