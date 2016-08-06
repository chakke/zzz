#include "SteeringUtils.hpp"
#include "../../ECS/Component/Components.hpp"
template<typename component_type>
component_type* getComponent(artemis::Entity* e) {
	return (component_type*)e->getComponent<component_type>();
};

SteeringUtils* _steering_instance = nullptr;
SteeringUtils * SteeringUtils::getInstance()
{
	if (!_steering_instance) {
		_steering_instance = new SteeringUtils();
	}
	return _steering_instance;
}

cocos2d::Vec2 SteeringUtils::seek(artemis::Entity * e, cocos2d::Vec2 target)
{
	auto entityPos = getComponent<PositionComponent>(e);
	auto entityVel = getComponent<VelocityComponent>(e);
	mTemp->set(target)->sub(entityPos->getPosition());
	mTemp->setLength(entityVel->getMaxVelocity());
	mTemp->sub(entityVel->getVelocity());
	mTemp->limit(entityVel->getMaxForce());
	return mTemp->toVec2();
}
cocos2d::Vec2 SteeringUtils::arrive(artemis::Entity * e, cocos2d::Vec2 target, float slowingRadius)
{
	if (slowingRadius <= 0) return seek(e, target);
	auto entityPos = getComponent<PositionComponent>(e);
	auto entityVel = getComponent<VelocityComponent>(e);
	mTemp->set(target);
	float dst = mTemp->dst(entityPos->getPosition());
	float speed = entityVel->getMaxVelocity();
	if (dst < slowingRadius) {
		speed = speed* dst / slowingRadius;
	}
	mTemp->sub(entityPos->getPosition());
	mTemp->setLength(speed);
	mTemp->sub(entityVel->getVelocity());
	mTemp->limit(entityVel->getMaxForce());
	return mTemp->toVec2();
}
cocos2d::Vec2 SteeringUtils::flee(artemis::Entity * e, cocos2d::Vec2 target)
{
	auto entityPos = getComponent<PositionComponent>(e);
	auto entityVel = getComponent<VelocityComponent>(e);
	mTemp->set(entityPos->getPosition())->sub(target);
	mTemp->setLength(entityVel->getMaxVelocity());
	mTemp->sub(entityVel->getVelocity())->limit(entityVel->getMaxForce());

	return mTemp->toVec2();
}
cocos2d::Vec2 SteeringUtils::pursuit(artemis::Entity * e, artemis::Entity * target,int nextGameStep)
{	
	auto tarPos = getComponent<PositionComponent>(target);
	auto tarVel = getComponent<VelocityComponent>(target);
	mTemp->set(tarVel->getVelocity())->scl(nextGameStep);
	mTemp->add(tarPos->getPosition());
	return seek(e,mTemp->toVec2());
}
cocos2d::Vec2 SteeringUtils::evade(artemis::Entity * e, artemis::Entity * target, const int nextGameStep)
{
	auto tarPos = getComponent<PositionComponent>(target);
	auto tarVel = getComponent<VelocityComponent>(target);
	mTemp->set(tarVel->getVelocity())->scl(nextGameStep);
	mTemp->add(tarPos->getPosition());
	return flee(e, mTemp->toVec2());
}
SteeringUtils::SteeringUtils()
{
	mTemp = new Vector2();
}
SteeringUtils::~SteeringUtils()
{
	CC_SAFE_RELEASE_NULL(mTemp);
}
