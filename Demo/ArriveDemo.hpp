#pragma once

#include "cocos2d.h"
#include "../artemis/Artemis.h"
#include "../Data/ObserverData.hpp"
#include "AbstractDemo.hpp"
#include "../ECS/TouchManager.hpp"
#include "../ECS/CameraManager.hpp"


class ArriveDemo : public AbstractDemo {
public:
	ArriveDemo();
	~ArriveDemo();
	void onRecieveCommand(int commandTag, std::shared_ptr<connection_object> data);	
protected:
	void onGlobalTap(std::shared_ptr<connection_object> data);
	void loadEntities();
	void loadSystemAndConfig();

};
