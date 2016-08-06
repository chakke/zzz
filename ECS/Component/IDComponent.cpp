#include "IDComponent.hpp"

IDComponent::IDComponent()
{
}

IDComponent::~IDComponent()
{
}

void IDComponent::setID(int type, int value)
{
	if (_ids.find(type) == _ids.end()) {
		_ids.insert(std::make_pair(type, value));
		return;
	}
	else {
		_ids.at(type) = value;
	}
}

void IDComponent::removeID(int type)
{
	if (_ids.find(type) != _ids.end()) {
		_ids.erase(type);
	}	
}
int IDComponent::getID(int type)
{
	if (_ids.find(type) == _ids.end()) {
		_ids.insert(std::make_pair(type, -1));
	}
	return _ids.at(type);
}

void IDComponent::setName(int type, std::string name)
{

	if (_names.find(type) == _names.end()) {
		_names.insert(std::make_pair(type, name));
		return;
	}
	else {
		_names.at(type) = name;
	}
}

std::string IDComponent::getName(int type)
{
	if (_names.find(type) == _names.end()) {
		_names.insert(std::make_pair(type, "undefined"));
	}
	return _names.at(type);
}
