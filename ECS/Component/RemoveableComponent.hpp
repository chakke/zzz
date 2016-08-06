#pragma once

#include "cocos2d.h"
#include "../../artemis/Component.h"
class RemoveableComponent : public artemis::Component {

public:
	RemoveableComponent(float time);
	~RemoveableComponent();
	
	float getRemainTime();
	void setRemainTime(float time);

protected:
	float mTime;
};
