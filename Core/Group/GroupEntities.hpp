#pragma once
#include "cocos2d.h"

class GroupEntities {
public:

	static GroupEntities* getInstance();
	void add(std::string group,int entityID);
	void remove(std::string group, int entityID);
	void removeAll(std::string group);
	std::vector<int> getEntites(std::string group);	
	bool has(std::string group);
private:
	std::map<std::string, std::vector<int>> _groups;
	GroupEntities();
};



