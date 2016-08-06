#pragma once
#include "cocos2d.h"
#include "Vector2.hpp"
#include "Poly.hpp"

/*
Written by Badlogic
Arcade Dota
20-04-2016
*/

namespace Intersector {
	
	 float distanceLinePoint(float startX, float startY, float endX, float endY, float pointX, float pointY);
	 float distanceLinePoint(Vector2* start, Vector2* end, Vector2* point);
	 float distanceLinePoint(cocos2d::Vec2 start, cocos2d::Vec2 end, cocos2d::Vec2 point);

	 cocos2d::Vec2 nearestSegmentPoint(float startX, float startY, float endX, float endY, float pointX, float pointY);
	 cocos2d::Vec2 nearestSegmentPoint(cocos2d::Vec2 start, cocos2d::Vec2 end, cocos2d::Vec2 point);
	 Vector2* nearestSegmentPoint(Vector2* start, Vector2* end, Vector2* point);

	 float distanceSegmentPoint(float startX, float startY, float endX, float endY, float pointX, float pointY);
	 float distanceSegmentPoint(cocos2d::Vec2 start, cocos2d::Vec2 end, cocos2d::Vec2 point);
	 float distanceSegmentPoint(Vector2* start, Vector2* end, Vector2* point);

	/** Returns true if the given point is inside the triangle. */
	 bool isPointInTriangle(float px, float py, float ax, float ay, float bx, float by, float cx, float cy);
	 bool isPointInTriangle(Vector2* p, Vector2* a, Vector2* b, Vector2* c);
	 bool isPointInTriangle(cocos2d::Vec2 p, cocos2d::Vec2 a, cocos2d::Vec2 b, cocos2d::Vec2 c);
	

	/** Determines on which side of the given line the point is. Returns -1 if the point is on the left side of the line, 0 if the
	* point is on the line and 1 if the point is on the right side of the line. Left and right are relative to the lines direction
	* which is linePoint1 to linePoint2. */
	 int pointLineSide(float linePoint1X, float linePoint1Y, float linePoint2X, float linePoint2Y, float pointX,
		float pointY);
	 int pointLineSide(cocos2d::Vec2 linePoint1, cocos2d::Vec2 linePoint2, cocos2d::Vec2 point);
	 int pointLineSide(Vector2* linePoint1, Vector2* linePoint2, Vector2* point);
	

	 bool intersectLines(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4,
		cocos2d::Vec2 intersection);
	 bool intersectLines(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4,
		Vector2* intersection);
	 bool intersectLines(cocos2d::Vec2 p1, cocos2d::Vec2 p2, cocos2d::Vec2 p3, cocos2d::Vec2 p4, cocos2d::Vec2 intersection);
	 bool intersectLines(Vector2* p1, Vector2* p2, Vector2* p3, Vector2* p4, Vector2* intersection);

	 bool isPointInPoly(std::vector<Vector2*> Poly, Vector2* point);
	 bool isPointInPoly(std::vector<float> Poly, int offset, int count, float x, float y);
	
	 bool intersectPolys(Poly* p1, Poly* p2, Poly* overlap);
	
	 bool intersectLinePoly(float x1, float y1, float x2, float y2, Poly* Poly);
	 bool intersectLinePoly(Vector2* p1, Vector2* p2, Poly* Poly);
	 bool intersectLinePoly(cocos2d::Vec2 p1, cocos2d::Vec2 p2, Poly* Poly);

	 bool intersectRects(Rect Rect1, Rect Rect2, Rect intersection);

	 bool intersectSegmentPoly(float x1,float y1,float x2,float y2, Poly* Poly);
	 bool intersectSegmentPoly(cocos2d::Vec2 p1, cocos2d::Vec2 p2, Poly* Poly);
	 bool intersectSegmentPoly(Vector2* p1, Vector2* p2, Poly* Poly);

	 bool intersectSegments(float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4, Vector2* intersection = nullptr);
	 bool intersectSegments(cocos2d::Vec2 p1, cocos2d::Vec2 p2, cocos2d::Vec2 p3, cocos2d::Vec2 p4, Vector2* intersection = nullptr);
	 bool intersectSegments(Vector2* p1, Vector2* p2, Vector2* p3, Vector2* p4, Vector2* intersection = nullptr);

};
