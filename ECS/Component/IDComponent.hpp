#pragma once

#include "cocos2d.h"
#include "../../artemis/Component.h"
/*
- Identify for spcific object
*/

class IDComponent : public artemis::Component {

public:
	IDComponent();
	~IDComponent();

	void setID(int type, int value);
	void removeID(int type);
	int getID(int type);

	void setName(int type, std::string name);
	std::string getName(int type);	
protected:	

	std::map<int,int> _ids;
	std::map<int, std::string> _names;
};
