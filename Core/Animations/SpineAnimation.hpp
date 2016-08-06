#pragma once

#include "cocos2d.h"
#include "EntityAnimation.hpp"
#include <spine/SkeletonAnimation.h>
class SpineAnimation : public EntityAnimation {

public:	
	SpineAnimation();
	~SpineAnimation();
	void animate(int name);
	void setup(int playSide, int entityType, cocos2d::Node* parent);	
	void setFlip(bool flip);
protected:
	spine::SkeletonAnimation* mSkeleton;
	std::map<int, std::string> _names;
};
