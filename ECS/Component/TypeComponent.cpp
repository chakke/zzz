#include "TypeComponent.hpp"



TypeComponent::TypeComponent(int entityType) : mEntityType(entityType){}

TypeComponent::~TypeComponent(){}

int TypeComponent::getEntityType()
{
	return mEntityType;
}

int TypeComponent::getType(int type)
{
	if (_types.find(type) != _types.end()) return _types.at(type);
	return -1;
}

void TypeComponent::setEntityType(int type)
{
	mEntityType = type;
}

void TypeComponent::setType(int type, int value)
{
	_types.insert(std::make_pair(type,value));
}

void TypeComponent::removeType(int type)
{
	if (_types.find(type) != _types.end()) _types.erase(type);
}

void TypeComponent::removeAllTypes()
{
	_types.clear();
}
