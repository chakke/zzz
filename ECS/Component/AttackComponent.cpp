#include "AttackComponent.hpp"

AttackComponent::AttackComponent(float damage) :mDamage(damage)
{
	timeAttack = .06f;
	time = 0;
}

AttackComponent::~AttackComponent()
{
}

void AttackComponent::setDamage(float damage)
{
	this->mDamage = damage;
}

float AttackComponent::getDamage()
{
	return mDamage;
}

bool AttackComponent::update(float dt)
{
	time += dt;
	if (time > timeAttack) {
		time = 0;
		return true;
	}
	return false;
}

void AttackComponent::setTime(float t)
{
	this->time = t;
}

void AttackComponent::setTimePerAttack(float t)
{
	this->timeAttack = t;
}
