#pragma once

#include "cocos2d.h"
#include "../../artemis/Component.h"

class TargetComponent : public artemis::Component {

public:
	TargetComponent();
	~TargetComponent();

	void setTargetID(int targetID);
	int getTargetID();
	bool hasTarget();
	bool hasGroupTarget();
	void removeTarget();
	void removeGroupTarget();
	void setGroup(std::string group);
	std::string getGroup();
protected :
	int mTargetID;
	std::string mGroup;
};
