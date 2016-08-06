
#include "SpineAnimation.hpp"
#include "../../Config/GameConstants.hpp"

SpineAnimation::SpineAnimation()
{
	_names.insert(std::make_pair(game::AnimationName::IDLE_UP,"b-idle"));
	_names.insert(std::make_pair(game::AnimationName::IDLE_DOWN, "f-idle"));
	_names.insert(std::make_pair(game::AnimationName::MOVE_UP, "b-walk"));
	_names.insert(std::make_pair(game::AnimationName::MOVE_DOWN, "f-walk"));
	_names.insert(std::make_pair(game::AnimationName::DIE_UP, "die"));
	_names.insert(std::make_pair(game::AnimationName::DIE_DOWN, "die"));
	_names.insert(std::make_pair(game::AnimationName::ATTACK_UP, "b-attack"));
	_names.insert(std::make_pair(game::AnimationName::ATTACK_DOWN, "f-attack"));
}

SpineAnimation::~SpineAnimation()
{
}
bool checkLoop(int animationName) {
	if (animationName == game::AnimationName::DIE_UP) return false;
	if (animationName == game::AnimationName::DIE_DOWN) return false;
	return true;
}
void SpineAnimation::animate(int name)
{
	if (!mSetup) return;
	if (name == mCurrentAnimation) return;
	mCurrentAnimation = name;
	if (needSetup()) return;
	if (!mSkeleton) return;
	if (_names.find(mCurrentAnimation) != _names.end()) {
		mSkeleton->setToSetupPose();
		mSkeleton->setAnimation(0, _names.at(mCurrentAnimation), checkLoop(mCurrentAnimation));
	}
}

void SpineAnimation::setup(int playSide, int entityType, cocos2d::Node * parent)
{
	
	mSkeleton = spine::SkeletonAnimation::createWithFile("spine/bobinh.json","spine/bobinh.atlas");
	mSkeleton->setSkin(cocos2d::StringUtils::format("%d",playSide));
	if (_names.find(mCurrentAnimation) != _names.end()) {		
		mSkeleton->setAnimation(0, _names.at(mCurrentAnimation), checkLoop(mCurrentAnimation));
	}
	mSkeleton->setScale(.2f);
	mSkeleton->setPositionY(-4);
	parent->addChild(mSkeleton);	
	mSetup = true;	
	CC_SAFE_RETAIN(mSkeleton);
}

void SpineAnimation::setFlip(bool flip)
{
if(mSetup && mSkeleton)	mSkeleton->setScaleX((flip ? -1 : 1)*mSkeleton->getScaleY());
}

