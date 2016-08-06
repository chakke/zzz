#pragma once

#include "cocos2d.h"
#include "../../artemis/Component.h"

class ScopeComponent : public artemis::Component {

public:
	
	ScopeComponent();
	~ScopeComponent();
	float getScope(int type);
	void setScope(int type,float scope);

protected:
	std::map<int, float> _scopes;
	
};
