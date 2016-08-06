#pragma once

#include "cocos2d.h"
#include "../../UIParser/CustomUI/CustomUIImageView.hpp"
class Builder {

public:	
	Builder();
	~Builder();
	virtual void updateProgress(float percent);
	virtual void onCreate(int type, int index);
	virtual void onBroken();	
	virtual void onFocus(bool focus = true);
	virtual void setVisible(bool visible);
	virtual void setLocalIndex(int index);
protected:
	CustomUIImageView* mImage;

};
