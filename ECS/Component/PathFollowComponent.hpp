#pragma once

#include "cocos2d.h"
#include "../../artemis/Component.h"
#include "../../Core/Math/Vector2.hpp"

struct WayPoint{
	cocos2d::Vec2 mPosition;
	float mEpsilon;
	WayPoint(float x, float y, float epsilon) {
		mPosition.set(x,y);
		mEpsilon = epsilon;
	}
	WayPoint(cocos2d::Vec2 pos, float epsilon) {
		mPosition.set(pos);
		mEpsilon = epsilon;
	}
};

class PathFollowComponent : public artemis::Component {

public:
	PathFollowComponent();
	~PathFollowComponent();

	void addWayPoint(cocos2d::Vec2 position, float epsilon, const bool isDestination = false);
	void addWayPoint(float x, float y,float epsilon, const bool isDestination = false);

	void setWayPoint(int index,float x, float y, float epsilon);
	void setWayPoint(int index, cocos2d::Vec2 position, float epsilon);
	
	void clear();
	bool hasNextPoint();
	std::vector<WayPoint> getWayPoints();

	WayPoint target();
	WayPoint peek();
	WayPoint pop();
protected:
	std::vector<WayPoint> _waypoints;

};
