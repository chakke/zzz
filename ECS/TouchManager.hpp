#pragma once
#include "cocos2d.h"

struct TrackData {
	long long _time;
	cocos2d::Vec2 _delta;
	TrackData(long long time, const cocos2d::Vec2 &delta) {
		_time = time;
		_delta.set(delta);
	}
};
struct VelocityTracker {

	bool mRunning;
	std::vector<TrackData> _dts;

	VelocityTracker() {
		mRunning = false;
	}
	void reset() {
		mRunning = false;
		_dts.clear();
	}
	void addData(const cocos2d::Vec2 &delta) {
		mRunning = true;
		_dts.push_back(TrackData(cocos2d::utils::getTimeInMilliseconds(), delta));
	}
	cocos2d::Vec2 getFlingVelocity() {
		if (_dts.size() == 0) return cocos2d::Vec2(0,0);

		long long currentTime = cocos2d::utils::getTimeInMilliseconds();
		int index = _dts.size() - 1;
		int time = 0;
		std::vector<TrackData> dts;
	
		while (time < 100 && index >= 0) {
			auto data = _dts.at(index);						
			dts.push_back(data);
			time = currentTime - data._time;
			index--;
		}
		float vx = 0;
		float vy = 0;

		for (int i = 0; i < dts.size(); i++) {
			vx += dts.at(i)._delta.x;
			vy += dts.at(i)._delta.y;
			
		}
		vx = vx / dts.size();
		vy = vy / dts.size();
		auto velocity = cocos2d::Vec2(vx, vy);		
		if (velocity.getLengthSq() <= 40) velocity.setZero();
		return velocity;
	}
};

struct SingleTouchData {
	float timeTouch;
	bool active;
	cocos2d::Vec2 startPosition;
	cocos2d::Vec2 movePosition;
	bool isMoved;
	SingleTouchData() {
		active = false;
		startPosition = cocos2d::Vec2();
		movePosition = cocos2d::Vec2();
		timeTouch = 0;
		isMoved = false;
	}

	void reset() {
		startPosition.setZero();
		movePosition.setZero();
		active = false;
		timeTouch = 0;
		isMoved = false;
	}

};


struct ZoomData {
	float begin_dst;
	float zoom_dst;
	bool isZoom;
	float lastZoomPercent;

	ZoomData() {
		isZoom = false;
		zoom_dst = 0;
		begin_dst = 0;
		lastZoomPercent = 1;
	}
	void setBeginDst(float beginDst) {
		begin_dst = beginDst;
		isZoom = true;
	}
	void setZoomDst(float zoomDst) {
		zoom_dst = zoomDst;
		isZoom = true;
	}
	void setLastZoomPercent(float lastZoom) {
		lastZoomPercent = lastZoom;
	}

	float getBeginDistance() {
		return begin_dst;
	}
	float getZoomDistance() {
		return zoom_dst;
	}
	float getLastZoomPercent() {
		return lastZoomPercent;
	}


	bool isZooming() {
		return isZoom;
	}
	void reset() {
		isZoom = false;
		zoom_dst = 0;
		begin_dst = 0;
		lastZoomPercent = 1;
	}

};


class TouchManager {
public:
	TouchManager();
	void update(float delta);
	void createTouch(cocos2d::Node* coordinator);
	void resetWhenEndTouch();
	void onTouchBegan(const std::vector<cocos2d::Touch*>& touchs, cocos2d::Event* event);
	void onTouchMoved(const std::vector<cocos2d::Touch*>& touchs, cocos2d::Event* event);
	void onTouchEnded(const std::vector<cocos2d::Touch*>& touchs, cocos2d::Event* event);
	virtual void initUI();
private:
	void onTap(float x, float y);
	void onFling(float x, float y, float vx, float vy);
	void onMove(float x, float y, float dx, float dy);
	void onZoom(float cx, float cy, float delta);

	float multiTouchDistance;
	float mTimeTouch;
	bool isTouching;



	std::map<int, cocos2d::Touch*> _touchs;
	void addTouch(cocos2d::Touch* touch);
	void removeTouch(int touchID);
	bool hasTouch(int touchID);
	cocos2d::Touch* getTouch(int touchID);
	cocos2d::Touch* getTouchByIndex(int index);
	ZoomData mZoomData;
	SingleTouchData mSingleTouchData;
	VelocityTracker mVelocityTracker;
};



