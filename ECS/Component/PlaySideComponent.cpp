#include "PlaySideComponent.hpp"

PlaySideComponent::PlaySideComponent()
{
	mSide = -1;
	mSideIndex = 0;
}

PlaySideComponent::~PlaySideComponent()
{
}

void PlaySideComponent::setSide(int side)
{
	this->mSide = side;
}

void PlaySideComponent::setSideIndex(int index)
{
	this->mSideIndex = index;
}

int PlaySideComponent::getSide()
{
	return mSide;
}

int PlaySideComponent::getSideIndex()
{
	return mSideIndex;
}
