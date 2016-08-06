#pragma once

#include "cocos2d.h"
#include "../../UIParser/CustomUI/CustomUIImageView.hpp"
#include "ui/CocosGUI.h"
class HPBar {

public:
	HPBar();
	~HPBar();
	 void setPercent(float percent, bool visible = true);
	 void onCreate(int playSide, const float percent = 1);
	 void setVisible(bool visible);
	 void setPlaySide(int playSide);
	 void setContentSize(cocos2d::Size size);
	 void free();
	 void enableBorder(bool enable);
	 void obtain(int playSide, cocos2d::Size size, float percent);
	 cocos2d::Node* getView();
	 
protected:
	cocos2d::Node* mRenderNode;
	CustomUIImageView* mBorder;
	CustomUIImageView* mNinePatch;
	cocos2d::ui::Text* mText;
	cocos2d::Size mContentSize;
	float mPercent;
	bool mFree;
};
