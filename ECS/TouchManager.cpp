#include "TouchManager.hpp"
#include "../Core/Command/CommandDispatcher.hpp"
#include "../Core/Command/Commands.hpp"
#include "../Core/Math/Vector2.hpp"
#include "ui/CocosGUI.h"

TouchManager::TouchManager() {
	cocos2d::Director::getInstance()->getScheduler()->scheduleUpdate(this, 1, false);
	resetWhenEndTouch();
	mZoomData.reset();
}
void TouchManager::createTouch(cocos2d::Node* node) {
	auto listener = cocos2d::EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(TouchManager::onTouchBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(TouchManager::onTouchMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(TouchManager::onTouchEnded, this);
	listener->onTouchesCancelled = CC_CALLBACK_2(TouchManager::onTouchEnded, this);
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, node);
	
}


void TouchManager::update(float delta) {
	isTouching = _touchs.size() > 0;
	if (mSingleTouchData.active) mSingleTouchData.timeTouch += delta;
}
void TouchManager::resetWhenEndTouch() {
	multiTouchDistance = 0;
	isTouching = false;
	mSingleTouchData.reset();
	mZoomData.reset();
	_touchs.clear();
}
void TouchManager::onTouchBegan(const std::vector<cocos2d::Touch*>& touchs, cocos2d::Event* event) {
	for (auto touch : touchs) {
		addTouch(touch);
	}

	if (touchs.size() >= 3) {
		_touchs.clear();
	}
	if (_touchs.size() == 1) {
		mSingleTouchData.active = true;
		mSingleTouchData.timeTouch = 0;
		mVelocityTracker.mRunning = true;		
	}
	CommandDispatcher::getInstance()->dispatch(command::STOP_FLING_GAME_CAMERA);
}
void TouchManager::onTouchMoved(const std::vector<cocos2d::Touch*>& touchs, cocos2d::Event* event) {
	if (touchs.size() == 1 && _touchs.size() == 1) {
		mVelocityTracker.addData(touchs.at(0)->getDelta());
		if (!mSingleTouchData.active) {
			mSingleTouchData.startPosition.set(touchs.at(0)->getLocation());
			mSingleTouchData.movePosition.set(touchs.at(0)->getLocation());
			mSingleTouchData.active = true;
			mSingleTouchData.isMoved = false;
		}
		else {
			float x = touchs.at(0)->getLocation().x;
			float y = touchs.at(0)->getLocation().y;
			float dx = x - touchs.at(0)->getPreviousLocation().x;
			float dy = y - touchs.at(0)->getPreviousLocation().y;
			onMove(x, y, dx, dy);
			mSingleTouchData.movePosition.set(touchs.at(0)->getLocation());
			if (abs(dx) > 3 || abs(dy) > 3) {
				mSingleTouchData.isMoved = true;
			}
		}
	}


	if (touchs.size() == 2 && _touchs.size() == 2) {
		auto touch1 = touchs.at(0);
		auto touch2 = touchs.at(1);
		if (mZoomData.isZooming()) {
			mZoomData.setZoomDst(touch1->getLocation().getDistance(touch2->getLocation()));
			float zoomPercent = mZoomData.begin_dst / mZoomData.zoom_dst;
			onZoom((touch1->getLocation().x + touch2->getLocation().x) / 2, (touch1->getLocation().y + touch2->getLocation().y) / 2, zoomPercent - mZoomData.lastZoomPercent);
			mZoomData.setLastZoomPercent(zoomPercent);
		}
		else {
			mZoomData.setBeginDst(touch1->getLocation().getDistance(touch2->getLocation()));
			mZoomData.setZoomDst(touch1->getLocation().getDistance(touch2->getLocation()));
		}
	}
	else {
		mZoomData.reset();
	}
}
void TouchManager::onTouchEnded(const std::vector<cocos2d::Touch*>& touchs, cocos2d::Event* event) {
	for (auto touch : touchs) {
		removeTouch(touch->getID());
	}
	if (_touchs.size() <= 1) {
		if (mZoomData.isZooming()) {
			CommandDispatcher::getInstance()->dispatch(command::ON_UNZOOM_CAMERA);
		}
		mZoomData.reset();
	}
	if (_touchs.size() == 0) {
		if (touchs.size() == 1) {										
			auto touch = touchs.at(0);
			if (mSingleTouchData.active) {				
				if (mSingleTouchData.timeTouch < .15f) {
					if (mSingleTouchData.isMoved)
						onFling(touch->getLocation().x, touch->getLocation().y, touch->getLocation().x - touch->getStartLocation().x, touch->getLocation().y - touch->getStartLocation().y);
					else
						onTap(touch->getLocation().x, touch->getLocation().y);
				}
				else {
					auto velocity = mVelocityTracker.getFlingVelocity();
					if (!velocity.isZero()) {
						onFling(0, 0, velocity.x, velocity.y);
					}
				}
			}
			auto obj = std::shared_ptr<connection_object>(new connection_object());
			obj->putFloat("x", touch->getLocation().x);
			obj->putFloat("y", touch->getLocation().y);
			CommandDispatcher::getInstance()->dispatch(command::ON_GLOBAL_TOUCH_END, obj);
		}	
		mVelocityTracker.reset();
		resetWhenEndTouch();
	}
}
void TouchManager::initUI() {


}
void TouchManager::addTouch(cocos2d::Touch* touch) {
	if (hasTouch(touch->getID())) return;
	_touchs.insert(std::make_pair(touch->getID(), touch));
}
void TouchManager::removeTouch(int touchID) {
	if (!hasTouch(touchID)) return;
	_touchs.erase(touchID);
}
bool TouchManager::hasTouch(int touchID) {
	return (_touchs.find(touchID) != _touchs.end());
}
cocos2d::Touch* TouchManager::getTouch(int touchID) {
	if (hasTouch(touchID)) return _touchs.at(touchID);
	return nullptr;
}
cocos2d::Touch* TouchManager::getTouchByIndex(int index) {
	int id = 0;
	for (auto touch : _touchs) {
		if (id == index) {
			return touch.second;
		}
		id++;
	}
	return nullptr;
}
void TouchManager::onTap(float x, float y) {
	auto obj = std::shared_ptr<connection_object>(new connection_object());
	obj->putFloat("x", x);
	obj->putFloat("y", y);
	CommandDispatcher::getInstance()->dispatch(command::ON_GLOBAL_TAP, obj);
}
void TouchManager::onFling(float x, float y, float vx, float vy) {
	auto obj = std::shared_ptr<connection_object>(new connection_object());
	obj->putFloat("x", x);
	obj->putFloat("y", y);
	obj->putFloat("vx", vx);
	obj->putFloat("vy", vy);

	CommandDispatcher::getInstance()->dispatch(command::ON_GLOBAL_FLING, obj);
}
void TouchManager::onMove(float x, float y, float dx, float dy) {
	auto dt = std::shared_ptr<connection_object>(new connection_object());
	dt->putFloat("x", x);
	dt->putFloat("y", y);
	dt->putFloat("dx", dx);
	dt->putFloat("dy", dy);
	CommandDispatcher::getInstance()->dispatch(command::ON_GLOBAL_TOUCH_MOVE, dt);
}
void TouchManager::onZoom(float cx, float cy, float delta) {
	auto dt = std::shared_ptr<connection_object>(new connection_object());
	dt->putFloat("delta", delta);
	dt->putFloat("x", cx);
	dt->putFloat("y", cy);
	CommandDispatcher::getInstance()->dispatch(command::ON_GLOBAL_ZOOM, dt);
}

