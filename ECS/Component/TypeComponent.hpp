#pragma once

#include "cocos2d.h"
#include "../../artemis/Component.h"

class TypeComponent : public artemis::Component {

public:	
	TypeComponent(int entityType = -1);
	~TypeComponent();
	int getEntityType();
	int getType(int type);
	void setEntityType(int type);
	void setType(int type,int value);
	void removeType(int type);
	void removeAllTypes();

protected:
	std::map<int, int> _types;
	int mEntityType;
};
