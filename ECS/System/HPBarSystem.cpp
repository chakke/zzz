#include "HPBarSystem.h"
#include "../Component/Components.hpp"
#include "../../Config/GameConstants.hpp"
HPBarSystem::HPBarSystem()
{
	addComponentType<HealthComponent>();
	addComponentType<StateComponent>();
}

void HPBarSystem::initialize()
{
	while (_bars.size() < 5) {
		_bars.push_back(new HPBar());
	}
}

void HPBarSystem::processEntity(artemis::Entity & e)
{
	auto stateComponent = getComponent<StateComponent>(e);
	if (stateComponent->getStateName() == game::state::DIE) {
		freeHPBar(e);
	}
	else {
		auto healthComponent = getComponent<HealthComponent>(e);
		if (healthComponent->getHealth() != healthComponent->getFullHealth()) {
			updateHPBar(e, healthComponent->getHealth() / healthComponent->getFullHealth());
		}
	}
}

void HPBarSystem::freeHPBar(artemis::Entity & e)
{
	if (_running_bars.find(e.getId()) != _running_bars.end()) {
		auto bar = _running_bars.at(e.getId());
		if (bar) {
			bar->free();
			_bars.push_back(bar);
		}
		_running_bars.erase(e.getId());		
	}
}

void HPBarSystem::updateHPBar(artemis::Entity & e, float percent)
{
	if (percent == 0) {
		this->freeHPBar(e);
		return;
	}

	if (_running_bars.find(e.getId()) == _running_bars.end()) {		
		int playSide = getComponent<PlaySideComponent>(e)->getSide();
		int entityType = getComponent<TypeComponent>(e)->getEntityType();
		if (entityType == game::entity::TROOP) {
			auto bar = this->obtain();
			bar->obtain(playSide,cocos2d::Size(40,6),percent);			
			bar->getView()->setPositionY(60);			
			getComponent<RenderComponent>(e)->getView()->addChild(bar->getView());
			_running_bars.insert(std::make_pair(e.getId(), bar));
		}
	}
	else {
		_running_bars.at(e.getId())->setPercent(percent);	
	}
}

HPBar * HPBarSystem::obtain()
{
	if (_bars.size() == 0) {
		auto bar = new HPBar();
		_bars.push_back(bar);
		return bar;
	}
	auto bar = _bars.at(_bars.size() - 1);
	_bars.pop_back();
	return bar;
}
