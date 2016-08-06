#pragma once

#include "cocos2d.h"
#include "../../artemis/Component.h"
class RenderSortableComponent : public artemis::Component {

public:
	RenderSortableComponent();
	~RenderSortableComponent();
	void setPiority(int piority);
	int getPiority();
protected:
	int mPiority;

};
