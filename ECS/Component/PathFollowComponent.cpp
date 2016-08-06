#include "PathFollowComponent.hpp"

PathFollowComponent::PathFollowComponent()
{
}

PathFollowComponent::~PathFollowComponent()
{
}

void PathFollowComponent::addWayPoint(cocos2d::Vec2 position, float epsilon, bool isDestination)
{
	if (hasNextPoint()) {
		if (peek().mPosition.fuzzyEquals(position, epsilon)) return;
	}

	if (isDestination)
	{
		if (hasNextPoint())
		{
			_waypoints.at(0).mPosition.set(position);
			_waypoints.at(0).mEpsilon = epsilon;
		}
		else {
			_waypoints.push_back(WayPoint(position, epsilon));
		}
	}
	else
	{
		_waypoints.push_back(WayPoint(position, epsilon));
	}

}

void PathFollowComponent::addWayPoint(float x, float y, float epsilon, bool isDestination)
{
	addWayPoint(cocos2d::Vec2(x, y), epsilon, isDestination);
}

void PathFollowComponent::setWayPoint(int index, float x, float y, float epsilon)
{
	if (index < _waypoints.size())
	{
		_waypoints.at(index).mPosition.set(x, y);
		_waypoints.at(index).mEpsilon = epsilon;
	}
	else if (index == _waypoints.size())
	{
		addWayPoint(x, y, epsilon);
	}
}

void PathFollowComponent::setWayPoint(int index, cocos2d::Vec2 pos, float epsilon)
{
	setWayPoint(index, pos.x, pos.y, epsilon);
}

void PathFollowComponent::clear()
{
	_waypoints.clear();
}

bool PathFollowComponent::hasNextPoint()
{
	return _waypoints.size() > 0;
}

std::vector<WayPoint> PathFollowComponent::getWayPoints()
{
	return _waypoints;
}

WayPoint PathFollowComponent::target()
{
	if (_waypoints.size() > 0) {
		return _waypoints.at(0);
	}
	return WayPoint(0, 0, 0);
}

WayPoint PathFollowComponent::peek()
{
	if (_waypoints.size() > 0) {
		return _waypoints.at(_waypoints.size() - 1);
	}
	return WayPoint(0, 0, 0);
}

WayPoint PathFollowComponent::pop()
{
	if (_waypoints.size() > 0) {
		auto point = _waypoints.at(_waypoints.size() - 1);
		_waypoints.pop_back();
		return point;
	}
	return WayPoint(0, 0, 0);
}
