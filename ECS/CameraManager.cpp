
#include "CameraManager.hpp"
#include "GameConfig.hpp"
#include "../Config/Cmd.hpp"
#include "../Core/Command/Commands.hpp"
#include "ui/CocosGUI.h"

CameraManager::CameraManager(cocos2d::ui::Layout * target)
{
	auto worldSize = game::config->getWorldSize();
	auto viewportSize = game::config->getViewportSize();
	auto winSize = cocos2d::Director::getInstance()->getWinSize();
	MIN_ZOOM = MAX(winSize.width / worldSize.width, winSize.height / worldSize.height) + .1f;
	ORIGIN_ZOOM = MIN(viewportSize.width / worldSize.width, viewportSize.height / worldSize.height) + .2f;
	MAX_ZOOM = 2.0f;
	this->mTarget = target;
	this->mTarget->setScale(ORIGIN_ZOOM);

	setCameraBound(-winSize.width / 2, -winSize.height / 2, winSize.width / 2, winSize.height / 2);
	mCameraVelocity = cocos2d::Vec2();
	mFlingTime = 0;
	isZooming = false;
	mZoomThreshold = .05f;
	mZoom = ORIGIN_ZOOM;
	{
		auto eventListener = cocos2d::EventListenerKeyboard::create();
		eventListener->onKeyReleased = [=](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
			switch (keyCode) {
			case  cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
				mZoom = 1.05*mZoom;
				break;
			case  cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
				mZoom = .95*mZoom;
				break;
			}
		};
		cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, target);
	}

	mPos = mTarget->getPosition();
	_moving_to_pos = false;
	mTemp = new Vector2();
}

void CameraManager::onRecieveCommand(int type, std::shared_ptr<connection_object> data)
{
	if (type == command::ON_MOVE_GAME_CAMERA) {
		this->onMoveCamera(data);
	}
	else if (type == command::ON_FLING_GAME_CAMERA) {
		this->onFlingCamera(data);
	}
	else if (type == command::ON_ZOOM_CAMERA) {
		this->onZoomCamera(data);
	}
	else if (type == command::ON_UNZOOM_CAMERA) {
		isZooming = false;
		mZoom = MIN(MAX_ZOOM - .4f, mZoom);
		mZoom = MAX(MIN_ZOOM + .05f, mZoom);
	}
	else if (type == command::ON_NEW_MATCH) {
		mZoom = ORIGIN_ZOOM;
	}
	else if (type == command::STOP_FLING_GAME_CAMERA) {
		mCameraVelocity.setZero();
		mFlingTime = 0;
	}
	else if (type == command::ON_FINISH_MATCH) {
		mZoom = MIN_ZOOM;
	}
	else if (type == command::ON_NEW_MATCH) {
		mTarget->setScale(MAX_ZOOM);
		mZoom = ORIGIN_ZOOM;
	}
	else if (type == cmd::camera::ZOOM_TO) {		
		mZoom = data->getFloat("zoom");
	}
}

void CameraManager::process(float delta)
{
	mFlingTime -= delta;
	if (mFlingTime < 0) mFlingTime = 0;
	if (mFlingTime > 0) {
		mTemp->set(mCameraVelocity)->setLength(10 * mFlingTime);
		getTarget()->setPositionX(getTarget()->getPositionX() + mTemp->getX());
		getTarget()->setPositionY(getTarget()->getPositionY() + mTemp->getY());
		clampCameraPosition();
	}

	if (_moving_to_pos) {
		float dx = mPos.x - getTarget()->getPositionX();
		float dy = mPos.y - getTarget()->getPositionY();
		getTarget()->setPositionX(getTarget()->getPositionX() + dx*mZoomThreshold);
		getTarget()->setPositionY(getTarget()->getPositionY() + dy*mZoomThreshold);
		clampCameraPosition();
	}
	clampCameraZoom();
}




void CameraManager::onMoveCamera(std::shared_ptr<connection_object> data)
{
	if (game::config->isBlockInput()) return;
	float dx = data->getFloat("dx");
	float dy = data->getFloat("dy");
	getTarget()->setPositionX(getTarget()->getPositionX() + dx);
	getTarget()->setPositionY(getTarget()->getPositionY() + dy);
	clampCameraPosition();
}

void CameraManager::onZoomCamera(std::shared_ptr<connection_object> data)
{

	if (game::config->isBlockInput()) return;
	isZooming = true;
	float cx = data->getFloat("x");
	float cy = data->getFloat("y");
	cocos2d::Vec2 pos = getTarget()->convertToNodeSpace(cocos2d::Vec2(data->getFloat("x"), data->getFloat("y")));
	updateAnchorpoint(pos.x, pos.y);

	float zoom = getTarget()->getScale() - data->getFloat("delta");
	if (zoom < MIN_ZOOM) zoom = MIN_ZOOM;
	if (zoom > MAX_ZOOM) zoom = MAX_ZOOM;
	mZoom = zoom;
	getTarget()->setScale(zoom);

	clampCameraPosition();
}

void CameraManager::onFlingCamera(std::shared_ptr<connection_object> data)
{
	if (game::config->isBlockInput()) return;
	float x = data->getFloat("x");
	float y = data->getFloat("y");
	float vx = data->getFloat("vx");
	float vy = data->getFloat("vy");
	mCameraVelocity.set(vx, vy);
	mFlingTime = 1;
}

void CameraManager::setCameraBound(float min_x, float min_y, float max_x, float max_y)
{
	MIN_X = min_x;
	MIN_Y = min_y;
	MAX_X = max_x;
	MAX_Y = max_y;
}

void CameraManager::lookAt(cocos2d::Vec2 pos, const bool force)
{
	if (force) {
		mTarget->setPosition(pos);
	}
	else {
		mPos = pos;
		_moving_to_pos = true;
	}
}

void CameraManager::clampCameraPosition()
{
	if (mTarget) {
		auto pos = mTarget->getPosition();
		float dx = (1 - getTarget()->getScaleX())* getTarget()->getAnchorPointInPoints().x;
		float dy = (1 - getTarget()->getScaleY())* getTarget()->getAnchorPointInPoints().y;

		pos.x += dx;
		pos.y += dy;

		float cw = mTarget->getContentSize().width*mTarget->getScaleX();
		float ch = mTarget->getContentSize().height*mTarget->getScaleY();

		if (pos.x > MIN_X) {
			mTarget->setPositionX(MIN_X - dx);
			_moving_to_pos = false;
		}
		if (pos.x + cw < MAX_X) {
			mTarget->setPositionX(MAX_X - dx - cw);
			_moving_to_pos = false;
		}

		if (pos.y > MIN_Y) {
			mTarget->setPositionY(MIN_Y - dy);
			_moving_to_pos = false;
		}
		if (pos.y + ch < MAX_Y) {
			mTarget->setPositionY(MAX_Y - dy - ch);
			_moving_to_pos = false;
		}
	}

}

void CameraManager::clampCameraZoom()
{
	mZoom = MIN(MAX_ZOOM, mZoom);
	mZoom = MAX(mZoom, MIN_ZOOM);
	if (!isZooming && getTarget()->getScale() != mZoom) {
		float scale = getTarget()->getScale() + (mZoom - getTarget()->getScale())*mZoomThreshold;
		getTarget()->setScale(scale);
		clampCameraPosition();
	}
}

void CameraManager::updateAnchorpoint(float ax, float ay)
{
	cocos2d::Vec2 lastAnchorpoint = getTarget()->getAnchorPointInPoints();
	getTarget()->setAnchorPoint(cocos2d::Vec2(ax / getTarget()->getContentSize().width, ay / getTarget()->getContentSize().height));
	getTarget()->setPositionX(getTarget()->getPositionX() + (1 - getTarget()->getScaleX())* (lastAnchorpoint.x - ax));
	getTarget()->setPositionY(getTarget()->getPositionY() + (1 - getTarget()->getScaleY())* (lastAnchorpoint.y - ay));
}

cocos2d::ui::Layout * CameraManager::getTarget()
{
	return mTarget;
}
