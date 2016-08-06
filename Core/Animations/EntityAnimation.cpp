#include "EntityAnimation.hpp"
#include "../../Config/GameConstants.hpp"
EntityAnimation::EntityAnimation()
{
	mCurrentAnimation = game::AnimationName::NONE;
	mSetup = false;
}

EntityAnimation::~EntityAnimation()
{
}

int EntityAnimation::getCurrentAnimation()
{
	return mCurrentAnimation;
}

bool EntityAnimation::needSetup()
{
	return !mSetup;
}

void EntityAnimation::setFlip(bool flip)
{
}
