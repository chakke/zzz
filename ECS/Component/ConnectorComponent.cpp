#include "ConnectorComponent.hpp"

ConnectorComponent::ConnectorComponent()
{
}

ConnectorComponent::~ConnectorComponent()
{
}

std::vector<IDComponent*> ConnectorComponent::getConnectors()
{
	return _connectors;
}

void ConnectorComponent::addConnector(IDComponent * idcomponent)
{
	_connectors.push_back(idcomponent);

}

void ConnectorComponent::clearConnectors()
{
	_connectors.clear();
}
