#include "ScopeComponent.hpp"

ScopeComponent::ScopeComponent() 
{
	
}

ScopeComponent::~ScopeComponent()
{
}

float ScopeComponent::getScope(int type)
{
	if (_scopes.find(type) == _scopes.end()) return -1;
	return _scopes.at(type);
}

void ScopeComponent::setScope(int type, float scope)
{
	_scopes.insert(std::make_pair(type,scope));
}

