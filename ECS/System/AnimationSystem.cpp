#include "AnimationSystem.h"
#include "../../Config/GameConstants.hpp"
AnimationSystem::AnimationSystem()
{
	addComponentType<RenderComponent>();
	addComponentType<AnimationComponent>();
	addComponentType<PlaySideComponent>();
	addComponentType<TypeComponent>();
}

void AnimationSystem::processEntity(artemis::Entity & e)
{
	auto animationComponent = getComponent<AnimationComponent>(e);
	if (!animationComponent->isActive()) return;
	if (animationComponent->needSetup()) {
		auto renderComponent = getComponent<RenderComponent>(e);
		auto playSideComponent = getComponent<PlaySideComponent>(e);
		auto typeComponent = getComponent<TypeComponent>(e);
		animationComponent->setup(playSideComponent->getSide(), typeComponent->getType(game::entity::TROOP), renderComponent->getView());
	}
}
