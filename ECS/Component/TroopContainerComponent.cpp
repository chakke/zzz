#include "TroopContainerComponent.hpp"

TroopContainerComponent::TroopContainerComponent() : mCapacity(20)
{
}

TroopContainerComponent::~TroopContainerComponent()
{
}

void TroopContainerComponent::setTroop(int playSide, int type, int num)
{
	num = MAX(num, 0);
	if (_side_troops.find(playSide) == _side_troops.end()) {
		std::map<int, int> troops;
		troops.insert(std::make_pair(type, num));
		_side_troops.insert(std::make_pair(playSide, troops));
	}
	else {
		if (_side_troops.at(playSide).find(type) == _side_troops.at(playSide).end()) {
			_side_troops.at(playSide).insert(std::make_pair(type, num));
		}
		else {
			_side_troops.at(playSide).at(type) = num;
		}
	}
}

int TroopContainerComponent::getTroop(int playSide, int type)
{
	if (_side_troops.find(playSide) != _side_troops.end()) {
		if (_side_troops.at(playSide).find(type) != _side_troops.at(playSide).end()) {
			return _side_troops.at(playSide).at(type);
		}
		else {
			_side_troops.at(playSide).insert(std::make_pair(type, 0));
		}
	}
	return 0;
}

int TroopContainerComponent::getTotalTroop(int playSide)
{
	if (_side_troops.find(playSide) != _side_troops.end()) {
		auto troops = _side_troops.at(playSide);
		int total = 0;
		for (auto troop : troops) {
			total += troop.second;
		}
		return total;
	}
	else {
		_side_troops.insert(std::make_pair(playSide, std::map<int, int>()));
	}
	return 0;
}

int TroopContainerComponent::getTotalTroop(int playSide, int type)
{
	if (_side_troops.find(playSide) != _side_troops.end()) {
		auto troops = _side_troops.at(playSide);
		for (auto troop : troops) {
			if (troop.first == type) return troop.second;
		}
	}
	else {
		_side_troops.insert(std::make_pair(playSide, std::map<int, int>()));
	}
	return 0;
}

void TroopContainerComponent::removeTroop(int playSide, int type, const int num)
{
	setTroop(playSide, type, getTroop(playSide, type) - num);
}

void TroopContainerComponent::addTroop(int playSide, int type, const int num)
{
	setTroop(playSide, type, getTroop(playSide, type) + num);
}

void TroopContainerComponent::removeAllTroop()
{
	_side_troops.clear();
}

void TroopContainerComponent::setCapacity(int capacity)
{
	this->mCapacity = capacity;
}

int TroopContainerComponent::getCapacity()
{
	return mCapacity;
}
