#pragma once

#include "cocos2d.h"
#include "../../artemis/Component.h"

class PlaySideComponent : public artemis::Component {

public:
	
	PlaySideComponent();
	~PlaySideComponent();

	void setSide(int side);
	void setSideIndex(int index);

	int getSide();
	int getSideIndex();
protected:
	int mSide;
	int mSideIndex;
	
};
