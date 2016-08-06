#pragma once
#include "../../artemis/Artemis.h"
#include "../Component/RenderSortableComponent.hpp"
#include "../Component/RenderComponent.hpp"

struct CompareableNode {
	int id;
	float x;
	float y;

	CompareableNode(float x, float y, int id) : x(x), y(y), id(id) {}

	CompareableNode() : x(0), y(0), id(-1) {}

};

class SortRenderSystem : public artemis::EntityProcessingSystem
{
public:
	SortRenderSystem();
	virtual void initialize();
	virtual void begin();
	virtual void processEntity(artemis::Entity &e);
	virtual void end();

protected:
	artemis::ComponentMapper<RenderSortableComponent> sortMapper;
	artemis::ComponentMapper<RenderComponent> renderMapper;
	std::vector<cocos2d::Node*> _nodes;
};

