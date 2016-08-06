#include "SpriteAnimation.hpp"
#include "../../UIParser/Atlas/AtlasCache.hpp"
#include "../../Config/GameConstants.hpp"
#include "../GameAnimations.hpp"


SpriteAnimation::SpriteAnimation()
{
	mCurrentAnimation = game::AnimationName::NONE;
	mSetup = false;
	mPlaySide = game::side::SIDE_1;
	mEntityType = game::troop::BABARIAN;
}

SpriteAnimation::~SpriteAnimation()
{
	CC_SAFE_RELEASE_NULL(mSprite);
}
void SpriteAnimation::animate(int name)
{
	if (needSetup()) { return; }

	if (name == mCurrentAnimation) return;
	this->animate(name, checkLoop(name));
}
int flagAnimation = 2222;
void SpriteAnimation::animate(int name, bool loop)
{
	this->mCurrentAnimation = name;
	auto animation = game::GameAnimations::getInstance()->getAnimation(getAnimationName(name));
	if (animation) {
		if (mSprite) {
			if (loop) {
				auto animated = cocos2d::RepeatForever::create(cocos2d::Animate::create(animation));
				animated->setFlags(flagAnimation);
				mSprite->stopActionsByFlags(flagAnimation);
				mSprite->runAction(animated);
			}
			else {
				cocos2d::Animate* animated = cocos2d::Animate::create(animation);
				animated->setFlags(flagAnimation);
				mSprite->stopActionsByFlags(flagAnimation);
				mSprite->runAction(animated);
			}
		}
	}
	else {
		//FIXME
		// cannot play animation : name
		CCLOG("Cannot play animation %d", name);
	}
}

void SpriteAnimation::setup(int playSide, int entityType, cocos2d::Node * parent)
{
	if (!mSetup) {
		mSetup = true;

		mPlaySide = playSide;
		mEntityType = entityType;

		auto animation = game::GameAnimations::getInstance()->getAnimation(getAnimationName(game::AnimationName::IDLE_UP));
		mSprite = cocos2d::Sprite::createWithSpriteFrame(animation->getFrames().at(0)->getSpriteFrame());
		mSprite->setAnchorPoint(cocos2d::Vec2(.5f, 0.1f));
		mSprite->setScale(.8f);
		
		mCurrentAnimation = game::AnimationName::NONE;
		this->animate(game::AnimationName::IDLE_UP);


		parent->addChild(mSprite);
		CC_SAFE_RETAIN(mSprite);

		
	}

}

int SpriteAnimation::getCurrentAnimation()
{
	return mCurrentAnimation;
}

bool SpriteAnimation::needSetup()
{
	return !mSetup;
}

void SpriteAnimation::setFlip(bool flip)
{
	if(mSetup && mSprite)mSprite->setScaleX((flip ? -1 : 1)*mSprite->getScaleY());
}

int SpriteAnimation::getAnimationName(int animation)
{
	return (mPlaySide - 1) * 100 + mEntityType * 20 + animation;
}

bool SpriteAnimation::checkLoop(int name)
{
	bool loop = true;
	switch (name)
	{
	case game::AnimationName::NONE:
	case game::AnimationName::DIE_UP:
	case game::AnimationName::DIE_DOWN:
		loop = false;
		break;

	default:
		loop = true;
		break;
	}
	return loop;
}


