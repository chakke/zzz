#include "GroupEntities.hpp"

GroupEntities * _group_instance = nullptr;
GroupEntities * GroupEntities::getInstance()
{
	if (!_group_instance) {
		_group_instance = new GroupEntities();
		return _group_instance;
	}
	return nullptr;
}

void GroupEntities::add(std::string group, int entityID)
{
	if (!has(group)) {
		_groups.insert(std::make_pair(group,std::vector<int>()));
	}	
	_groups.at(group).push_back(entityID);
}
void GroupEntities::remove(std::string group, int entityID) {
	/*do nothing here*/
	if (has(group)) {
		std::remove(_groups.at(group).begin(), _groups.at(group).end(), entityID);
	}
}

void GroupEntities::removeAll(std::string group)
{
	if (has(group)) {
		_groups.at(group).clear();
	}
}

std::vector<int> GroupEntities::getEntites(std::string group)
{
	if (has(group)) {
		return _groups.at(group);
	}
	return std::vector<int>();
}

bool GroupEntities::has(std::string group)
{
	return _groups.find(group) != _groups.end();
}

GroupEntities::GroupEntities() {}
