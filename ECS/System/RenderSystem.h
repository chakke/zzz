#pragma once
#include "../../artemis/Artemis.h"
#include "../Component/RenderComponent.hpp"
#include "../Component/PositionComponent.hpp"

class RenderSystem : public artemis::EntityProcessingSystem
{
public:
	RenderSystem(cocos2d::ui::Layout* root);
	virtual void initialize();
	virtual void begin();
	virtual void processEntity(artemis::Entity &e);
	virtual void end();	
protected:
	artemis::ComponentMapper<PositionComponent> positionMapper;
	artemis::ComponentMapper<RenderComponent> renderMapper;
	cocos2d::ui::Layout* mGameLayout;
};

