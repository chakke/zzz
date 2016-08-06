#pragma once

#include "cocos2d.h"
#include "../../artemis/Component.h"
#include "../../Data/ConnectionData.hpp"

class StateComponent : public artemis::Component {

public:
	StateComponent(int stateName, std::shared_ptr<connection_object> stateData);
	StateComponent();
	~StateComponent();

	void setState(int stateName, const std::shared_ptr<connection_object> data = nullptr);
	int getStateName();
	std::shared_ptr<connection_object> getStateData();
protected:
	int mStateName;
	std::shared_ptr<connection_object> mStateData;
};
