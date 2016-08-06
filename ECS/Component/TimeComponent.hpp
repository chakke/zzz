#pragma once

#include "cocos2d.h"
#include "../../artemis/Component.h"

class TimeComponent : public artemis::Component{

public :
	TimeComponent();

	void setCurrentTime(float currentTime);
	void setMaxTime(float mMaxTime);
	void setDirty(bool dirty);
	void setActive(bool active);


	bool isDirty();
	bool isActive();


	float getCurrentTime();
	float getMaxTime();
	void cloneFrom(TimeComponent* timeComponent);

protected :
	float mCurrent;
	float mMax;
	bool mActive;
	bool mDirty;
};
