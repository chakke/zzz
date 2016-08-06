#pragma once
#include "cocos2d.h"
/*
Written by Badlogic
Arcade Dota
20-04-2016
*/

class Vector2 :public cocos2d::Ref {
public:
	Vector2(float x, float y);
	Vector2(Vector2* other);
	Vector2();
	Vector2(cocos2d::Vec2 pos);
	~Vector2();
	Vector2* copy();

	Vector2* set(cocos2d::Vec2 other);
	Vector2* set(Vector2* other);
	Vector2* set(float x, float y);

	Vector2* sub(cocos2d::Vec2 other);
	Vector2* sub(Vector2* other);
	Vector2* sub(float x, float y);

	Vector2* add(cocos2d::Vec2 other);
	Vector2* add(Vector2* other);
	Vector2* add(float x, float y);

	Vector2* scl(float scale);
	Vector2* scl(float x, float y);
	Vector2* scl(cocos2d::Vec2 other);
	Vector2* scl(Vector2* other);

	Vector2* limit(float length);
	Vector2* limit2(float length2);

	Vector2* lerp(Vector2* target, float accurate);
	Vector2* lerp(cocos2d::Vec2 target, float accurate);

	Vector2* clamp(float min, float max);

	Vector2* setLength(float length);
	Vector2* setLength2(float length2);

	std::string toString();

	bool equal(float x, float y);
	bool equal(cocos2d::Vec2 other);
	bool equal(Vector2* other);

	bool epsilonEquals(float x, float y, float epsilon);
	bool epsilonEquals(cocos2d::Vec2 other, float epsilon);
	bool epsilonEquals(Vector2* other, float epsilon);
	bool isZero();

	float len();
	float len2();

	float dst(cocos2d::Vec2 other);
	float dst(Vector2* other);
	float dst(float x, float y);

	float dst2(cocos2d::Vec2 other);
	float dst2(Vector2* other);
	float dst2(float x, float y);

	float dot(float x, float y);
	float dot(cocos2d::Vec2 val);
	float dot(Vector2* val);

	float crs(float x, float y);
	float crs(cocos2d::Vec2 val);
	float crs(Vector2* val);



	Vector2* normalize();
	Vector2* setZero();

	Vector2* setX(float x);
	Vector2* setY(float y);

	float getX();
	float getY();

	float angle();
	float angle(float x, float y);
	float angle(cocos2d::Vec2 other);
	float angle(Vector2* other);

	float angleRad();
	float angleRad(float x, float y);
	float angleRad(cocos2d::Vec2 other);
	float angleRad(Vector2* other);


	Vector2* setAngle(float degrees);
	Vector2* setAngleRad(float radians);
	Vector2* rotate(float degrees);
	Vector2* rotateRad(float radians);

	bool isOnLine(float x, float y);
	bool isOnLine(cocos2d::Vec2 other);
	bool isOnLine(Vector2* other);



	bool isOnLine(float x, float y, float epsilon);
	bool isOnLine(cocos2d::Vec2 other, float epsilon);
	bool isOnLine(Vector2* other, float epsilon);


	bool isCollinear(float x, float y);
	bool isCollinear(cocos2d::Vec2 other);
	bool isCollinear(Vector2* other);


	bool isCollinear(float x, float y, float epsilon);
	bool isCollinear(cocos2d::Vec2 other, float epsilon);
	bool isCollinear(Vector2* other, float epsilon);


	bool isCollinearOpposite(float x, float y);
	bool isCollinearOpposite(cocos2d::Vec2 other);
	bool isCollinearOpposite(Vector2* other);

	bool isCollinearOpposite(float x, float y, float epsilon);
	bool isCollinearOpposite(cocos2d::Vec2 other, float epsilon);
	bool isCollinearOpposite(Vector2* other, float epsilon);

	bool isPerpendicular(float x, float y);
	bool isPerpendicular(cocos2d::Vec2 other);
	bool isPerpendicular(Vector2* other);

	bool isPerpendicular(float x, float y, float epsilon);
	bool isPerpendicular(cocos2d::Vec2 other, float epsilon);
	bool isPerpendicular(Vector2* other, float epsilon);


	bool hasSameDirection(float x, float y);
	bool hasSameDirection(cocos2d::Vec2 other);
	bool hasSameDirection(Vector2* other);

	bool hasOppositeDirection(float x, float y);
	bool hasOppositeDirection(cocos2d::Vec2 other);
	bool hasOppositeDirection(Vector2* other);

	cocos2d::Vec2 toVec2();

	float x;
	float y;
};

