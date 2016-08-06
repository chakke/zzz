#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
enum class Align{
	LEFT, BOTTOM_LEFT, BOTTOM, BOTTOM_RIGHT, RIGHT, TOP_RIGHT, TOP, TOP_LEFT, CENTER
};

class Alignment{
public:

	static void setPosition(cocos2d::Node* node, float x, float y, Align align);
	static float getX(cocos2d::Node* node, Align align);
	static void setX(cocos2d::Node* node,float x, Align align);
	static float getY(cocos2d::Node* node, Align align);
	static void setY(cocos2d::Node* node, float y, Align align);
	static cocos2d::Vec2 getPosition(cocos2d::Node* node, Align align);
};



