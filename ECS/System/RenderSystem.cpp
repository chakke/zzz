#include "RenderSystem.h"

RenderSystem::RenderSystem(cocos2d::ui::Layout* gameLayout)
{
	addComponentType<PositionComponent>();
	addComponentType<RenderComponent>();
	this->mGameLayout = gameLayout;
}
void RenderSystem::initialize() {
	positionMapper.init(*world);
	renderMapper.init(*world);
}

void RenderSystem::begin() {}

void RenderSystem::processEntity(artemis::Entity &e) {	

	auto pos= positionMapper.get(e);
	auto render = renderMapper.get(e);
	if (!render->getView()) return;
	if (!pos->isActive()) return;
	if (!render->isActive()) return;
	if (!render->isLinked()) {
		render->setDelayTime(render->getDelayTime() - world->getDelta());
		if (render->getDelayTime() <= 0) {
			render->linkTo(mGameLayout);
			render->setDelayTime(0);
		}
	}	
	render->getView()->setPosition(pos->getPosition()->toVec2());	
}
void RenderSystem::end() {}

