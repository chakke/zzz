#include "TargetComponent.hpp"

TargetComponent::TargetComponent()
{
	mTargetID = -1;
	mGroup = "undefined";
}

TargetComponent::~TargetComponent()
{
	
}

void TargetComponent::setTargetID(int targetID)
{
	mTargetID = targetID;
}

int TargetComponent::getTargetID()
{
	return mTargetID;
}

bool TargetComponent::hasTarget()
{
	return mTargetID != -1;
}

bool TargetComponent::hasGroupTarget()
{
	return strcmp(this->mGroup.c_str(),"undefined") != 0;
}

void TargetComponent::removeTarget()
{
	mTargetID = -1;
}

void TargetComponent::removeGroupTarget()
{
	mGroup = "undefined";
}

void TargetComponent::setGroup(std::string group)
{
	this->mGroup = group;
}

std::string TargetComponent::getGroup()
{
	return mGroup;
}
