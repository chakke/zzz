#include "HealthComponent.hpp"

HealthComponent::HealthComponent(float health) : mHealth(health) ,mFullHealth(health)
{

}

HealthComponent::~HealthComponent()
{
}

bool HealthComponent::beDamage(float damage)
{
	this->mHealth = MAX(this->mHealth - damage, 0);
	return this->mHealth == 0;
}

void HealthComponent::setHealth(float health, bool fullHealth)
{
	this->mHealth = health;
	if (fullHealth) this->setFullHealth(health);
}

void HealthComponent::setFullHealth(float health)
{
	mFullHealth = health;
}


float HealthComponent::getHealth()
{
	return mHealth;
}

float HealthComponent::getFullHealth()
{
	return mFullHealth;
}


int HealthComponent::getNumberOfAttacker()
{
	return _attackers.size();
}

std::vector<int> HealthComponent::getAttackers()
{
	return _attackers;
}



void HealthComponent::addAttacker(int id)
{
	if (std::find(_attackers.begin(), _attackers.end(), id) == _attackers.end()) {
		_attackers.push_back(id);
	}
}

void HealthComponent::removeAllAttacker()
{
	_attackers.clear();
}

void HealthComponent::removeAttacker(int id)
{
	if (std::find(_attackers.begin(), _attackers.end(), id) != _attackers.end()) {
		std::remove(_attackers.begin(), _attackers.end(),id);
	}
}

bool HealthComponent::hasAttacker()
{
	return _attackers.size()>0;
}
