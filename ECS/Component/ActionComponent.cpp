#include "ActionComponent.hpp"
#include "../../Config/GameConstants.hpp"
ActionComponent::ActionComponent()
{
}

ActionComponent::~ActionComponent()
{
}

void ActionComponent::addAction(int name, float delay, std::shared_ptr<connection_object> data)
{
	_actions.push_back(actioncomponent::Action(name, delay, data));
}

void ActionComponent::setAction(int name, float delay, std::shared_ptr<connection_object> data)
{
	removeAllActions();
	addAction(name, delay, data);
}

void ActionComponent::removeAction(int name)
{
	for (auto index = 0; index < _actions.size(); index++) {
		auto action = _actions.at(index);
		if (action.name == name) {
			_actions.erase(_actions.begin() + index);
			return;
		}
	}
}



std::vector<actioncomponent::Action> ActionComponent::getActions()
{
	return _actions;
}

actioncomponent::Action ActionComponent::getRunningAction()
{

	if (_actions.size() == 0) { return actioncomponent::Action(game::action::NONE, 0, nullptr); }
	return _actions.at(_actions.size() - 1);
}

void ActionComponent::removeAllActions()
{
	_actions.clear();
}

actioncomponent::Action ActionComponent::pop()
{
	auto runningAction = getRunningAction();
	if (_actions.size() > 0) _actions.pop_back();
	return runningAction;
}

actioncomponent::Action ActionComponent::peek()
{
	if (_actions.size() == 0) return actioncomponent::Action(game::action::NONE, 0, nullptr);
	return _actions.at(_actions.size() - 1);
}
