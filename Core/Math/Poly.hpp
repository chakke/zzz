#pragma once
#include "cocos2d.h"
USING_NS_CC; 
/*
Written by Badlogic
Arcade Dota
20-04-2016
*/
class Poly {
public:
	Poly();
	Poly(std::vector<float> vertices);
	std::vector<float> getVertices();
	std::vector<float> getTransformedVertices();

	void setOrigin(float x,float y);
	void setVertices(std::vector<float> vertice);
	void translate(float x, float y);
	void setRotation(float degrees);
	void rotate(float degrees);
	void setScale(float scaleX,float scaleY);
	void scale(float amount);
	void setDirty(bool dirty);
	float	area();
	Rect getBoundingBox();
	bool contains(float x,float y);
	bool contains(Vec2 point);
	
	float getX();
	float getY();
	float getOriginX();
	float getOriginY();
	float getRotation();
	float getScaleX();
	float getScaleY();

	void reset();
private :
	std::vector<float> localVertices;
	std::vector<float> worldVertices;
	float x;
	float y;
	float originX;
	float originY;
	float rotation;
	float scaleX = 1;
	float scaleY = 1;
	bool dirty;
	Rect bounds;
};
