#include "AttackSystem.h"
#include "../Component/Components.hpp"
#include "../../Config/GameConstants.hpp"
AttackSystem::AttackSystem()
{
	addComponentType<PositionComponent>();
	addComponentType<TargetComponent>();
	addComponentType<AttackComponent>();
	addComponentType<ScopeComponent>();
	addComponentType<StateComponent>();
}

void AttackSystem::processEntity(artemis::Entity & e)
{
	if (getComponent<StateComponent>(e)->getStateName() != game::state::TROOP_ATTACK) return;
	auto targetComponent = getComponent<TargetComponent>(e);
	if (!targetComponent->hasTarget()) {
		this->lookForTarget(e);
		return;
	}
	auto target = &world->getEntityManager()->getEntity(targetComponent->getTargetID());
	if (target) {
		auto positionComponent = getComponent<PositionComponent>(e);
		auto targetPosition = getComponent<PositionComponent>(*target)->getPosition();
		float dst = targetPosition->dst(positionComponent->getPosition());
		float scopeAttack = getComponent<ScopeComponent>(e)->getScope(game::scope::ATTACK);
		auto animationComponent = getComponent<AnimationComponent>(e);
		if (animationComponent) {
			getComponent<PathFollowComponent>(e)->addWayPoint(targetPosition->toVec2(), scopeAttack - 4, true);
			if (dst < scopeAttack) {
				animationComponent->animate(animationComponent->getCurrentAnimation() % 2 == 1 ? game::AnimationName::ATTACK_UP : game::AnimationName::ATTACK_DOWN);
				auto attackComponent = getComponent<AttackComponent>(e);
				if (attackComponent->update(world->getDelta())) {
					this->doAttack(e,*target);
				}
			}
			else {
				auto velocity = getComponent<VelocityComponent>(e)->getVelocity();
				float moveUp = velocity->getY() > 0;
				bool flip = velocity->getX() < 0;
				animationComponent->animate(moveUp ? game::AnimationName::MOVE_UP : game::AnimationName::MOVE_DOWN);
				animationComponent->setFlip(flip);
			}
		}

	}
}

void AttackSystem::lookForTarget(artemis::Entity & e)
{
	auto targetComponent = getComponent<TargetComponent>(e);
	if (targetComponent->hasTarget()) return;
	if (targetComponent->hasGroupTarget()) {
		auto scopeComponent = getComponent<ScopeComponent>(e);
		auto position = getComponent<PositionComponent>(e)->getPosition();
		int threadID = -1;
		float minDst = 1000000;
		auto targets = world->getGroupManager()->getEntities(targetComponent->getGroup());
		for (auto i = 0; i < targets->getCount(); i++) {
			auto target = targets->get(i);
			auto targetState = getComponent<StateComponent>(*target);
			if (targetState->getStateName() != game::state::DIE) {
				float dst = getComponent<PositionComponent>(*target)->getPosition()->dst2(position);
				if (dst < minDst) {
					minDst = dst;
					threadID = i;
				}
			}			
		}

		if (threadID != -1) {
			targetComponent->setTargetID(targets->get(threadID)->getId());			
		}
	}
}



void AttackSystem::doAttack(artemis::Entity & attacker, artemis::Entity & victim)
{
	auto attackComponent = getComponent<AttackComponent>(attacker);
	auto victimState = getComponent<StateComponent>(victim);
	if (victimState->getStateName() != game::state::DIE) {
		auto healthComponent = getComponent<HealthComponent>(victim);		
		if (healthComponent->beDamage(attackComponent->getDamage())) {
			victimState->setState(game::state::DIE);			
			getComponent<ActionComponent>(victim)->addAction(game::action::DIE_ON_ATTACK);
			getComponent<ActionComponent>(attacker)->addAction(game::action::KILLED_ENEMY);
			getComponent<TargetComponent>(attacker)->removeTarget();
		}
		
	}
}
