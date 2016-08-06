#pragma once

#include "cocos2d.h"
#include "../artemis/Artemis.h"
#include "../Data/ObserverData.hpp"
#include "../Core/AbstractGame.hpp"
#include "../ECS/TouchManager.hpp"
#include "../ECS/CameraManager.hpp"


class AbstractDemo : public AbstractGame {
public:
	AbstractDemo();
	~AbstractDemo();

	void onAdded();
	void onRemoved();

	void process(float delta);
	void initGameLayout(cocos2d::Size worldSize, cocos2d::Node* parent);
	void onRecieveCommand(int commandTag, std::shared_ptr<connection_object> data);
	void createWorld();
	
protected:
	virtual void loadSystemAndConfig();
	virtual void loadEntities();

	void onGlobalTap(std::shared_ptr<connection_object> data);
	void onGlobalTouchMove(std::shared_ptr<connection_object> data);
	void onGlobalTouchEnd(std::shared_ptr<connection_object> data);
	void onGlobalTouchZoom(std::shared_ptr<connection_object> data);
	void onGlobalTouchFling(std::shared_ptr<connection_object> data);
	cocos2d::Vec2 convertToGameSpace(cocos2d::Vec2 pos);
	artemis::EntitySystem* addSystem(artemis::EntitySystem* system);

	TouchManager* mTouchManager;
	CameraManager* mCameraManager;


};
