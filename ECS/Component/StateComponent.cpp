
#include "StateComponent.hpp"

StateComponent::StateComponent(int stateName, std::shared_ptr<connection_object> stateData) : mStateName(stateName),mStateData(stateData)
{
}

StateComponent::StateComponent()
{
	mStateName = -1;
	mStateData = nullptr;
}

StateComponent::~StateComponent()
{
}

void StateComponent::setState(int stateName, const std::shared_ptr<connection_object> data)
{
	mStateName = stateName;
	mStateData = data;
}

int StateComponent::getStateName()
{
	return mStateName;
}

std::shared_ptr<connection_object> StateComponent::getStateData()
{
	return mStateData;
}
