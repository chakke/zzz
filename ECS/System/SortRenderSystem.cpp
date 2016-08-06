#include "SortRenderSystem.h"

struct compareNodeBaseOnPosition
{
	inline bool operator() (const cocos2d::Node* node1, const cocos2d::Node* node2)
	{
		float dt = node2->getPositionY() - node1->getPositionY();
		if (dt == 0) dt = node2->getPositionX() - node1->getPositionX();
		return (dt < 0);
	}
};



struct compareNodeBase
{
	inline bool operator() (const CompareableNode &node1, const CompareableNode &node2)
	{
		float dt = node2.y - node1.y;
		if (dt == 0) dt = node2.x - node1.x;
		return (dt < 0);
	}
};
SortRenderSystem::SortRenderSystem()
{
	addComponentType<RenderSortableComponent>();
	addComponentType<RenderComponent>();	
}
void SortRenderSystem::initialize(){
	sortMapper.init(*world);
	renderMapper.init(*world);	
}

void SortRenderSystem::begin(){	
	_nodes.clear();
}

void SortRenderSystem::processEntity(artemis::Entity &e){
	if (sortMapper.get(e)->isActive()) {
		auto renderComponent = renderMapper.get(e);
		_nodes.push_back(renderComponent->getView());
	}
}

void SortRenderSystem::end(){

	if (_nodes.size() > 0) {
		std::sort(_nodes.begin(), _nodes.end(), compareNodeBaseOnPosition());
		int localz = 10;
		for (auto node : _nodes) {
			node->setLocalZOrder(localz++);
		}
	}
}

