#include "AnimationComponent.hpp"
#include "../../Config/GameConstants.hpp"
AnimationComponent::AnimationComponent(EntityAnimation* animation)
{
	mAnimation = animation;
}

AnimationComponent::~AnimationComponent()
{
}

int AnimationComponent::getCurrentAnimation()
{
	return mAnimation->getCurrentAnimation();
}

void AnimationComponent::animate(int name)
{
	if(mAnimation)	mAnimation->animate(name);
}

void AnimationComponent::setup(int playSide, int entityType, cocos2d::Node * parent)
{
	if (mAnimation)mAnimation->setup(playSide,entityType,parent);
}

bool AnimationComponent::needSetup()
{
	return mAnimation->needSetup();
}

void AnimationComponent::setFlip(bool flip)
{
	if (mAnimation) mAnimation->setFlip(flip);
}
