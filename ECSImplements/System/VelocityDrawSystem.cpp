#include "VelocityDrawSystem.h"
#include "../../ECS/Component/Components.hpp"
#include "../../Config/GameConstants.hpp"

VelocityDrawSystem::VelocityDrawSystem()
{
	addComponentType<PositionComponent>();
	addComponentType<VelocityComponent>();
	addComponentType<RenderComponent>();

	mTemp = new Vector2();
}

void VelocityDrawSystem::initialize()
{
	velocityMapper.init(*world);
	positionMapper.init(*world);
	renderMapper.init(*world);
}
int idxxx = 0;
void VelocityDrawSystem::begin()
{
	idxxx = 0;
}

void VelocityDrawSystem::processEntity(artemis::Entity & e)
{
	auto velocityComponent = velocityMapper.get(e);
	auto renderComponent = renderMapper.get(e);
	auto positionComponent = positionMapper.get(e);

	if (!renderComponent->getView()->getParent()) return;

	if (renderComponent->getView()->getParent()->getChildByName("drawvelocity") == nullptr) {
		auto drawnode = cocos2d::DrawNode::create();
		drawnode->setName("drawvelocity");
		renderComponent->getView()->getParent()->addChild(drawnode);
	}
	auto drawnode = (cocos2d::DrawNode*) renderComponent->getView()->getParent()->getChildByName("drawvelocity");
	if (idxxx++ == 0) drawnode->clear();
	mTemp->set(velocityComponent->getVelocity())->add(positionComponent->getPosition());	
	drawnode->drawLine(positionComponent->getPosition()->toVec2(), mTemp->toVec2(), cocos2d::Color4F::BLACK);

}
