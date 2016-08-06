#include "BuilderComponent.hpp"
#include "../../Config/GameConstants.hpp"
BuilderComponent::BuilderComponent()
{
	mType = game::troop::NONE;
	mBuildTime = 3;
	mEnable = true;
	mTime = mBuildTime;
}

BuilderComponent::~BuilderComponent()
{
}

void BuilderComponent::setType(int type)
{
	mType = type;
}

void BuilderComponent::setBuildTime(float time)
{
	this->mBuildTime = time;
}

void BuilderComponent::setEnable(bool enable)
{
	mEnable = enable;
}

bool BuilderComponent::update(float delta)
{
	if (mEnable) {
		mTime -= delta;		
		if (mTime <= 0) {			
			mTime = 0;
			return true;
		}
	}
	return false;
}

void BuilderComponent::startBuild()
{
	mTime = mBuildTime;
	mEnable = true;
}

int BuilderComponent::getType()
{
	return mType;
}

float BuilderComponent::getProgress()
{
	return mTime / mBuildTime;
}

void BuilderComponent::setProgress(float progress)
{
	mTime = progress*mBuildTime;
}
