#pragma once

#include "cocos2d.h"
#include "../../artemis/Component.h"
#include "IDComponent.hpp"
class ConnectorComponent : public artemis::Component {

public:
	ConnectorComponent();
	~ConnectorComponent();
	std::vector<IDComponent*> getConnectors();
	void addConnector(IDComponent* idcomponent);
	void clearConnectors();
protected:
	std::vector<IDComponent*> _connectors;
};
