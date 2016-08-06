#pragma once
#include "cocos2d.h"
#include "ui/UILayout.h"
#include "../Core/Command/CommandObserver.hpp"
#include "../Core/Math/Vector2.hpp"
class CameraManager :public CommandObserver{
public :
	CameraManager(cocos2d::ui::Layout* mTarget);	
	virtual void onRecieveCommand(int commandTag, std::shared_ptr<connection_object> data);
	virtual void process(float delta);
	virtual void setCameraBound(float x, float y, float width, float height);
	virtual void lookAt(cocos2d::Vec2 pos,const bool force = true);
protected :
	virtual void onMoveCamera(std::shared_ptr<connection_object> data);
	virtual void onZoomCamera(std::shared_ptr<connection_object> data);
	virtual void onFlingCamera(std::shared_ptr<connection_object> data);
	void clampCameraPosition();
	void clampCameraZoom();
private :
	virtual void updateAnchorpoint(float ax, float ay);
	virtual cocos2d::ui::Layout* getTarget();
	
	cocos2d::ui::Layout* mTarget;

	float ORIGIN_ZOOM;
	float MAX_ZOOM;
	float MIN_ZOOM;
	float MIN_X;
	float MIN_Y;
	float MAX_X;
	float MAX_Y;

	float mZoom;
	bool isZooming;
	float mZoomThreshold;
	float mFlingTime;
	cocos2d::Vec2 mCameraVelocity;
	cocos2d::Vec2 mPos;
	Vector2* mTemp;
	bool _moving_to_pos;
};