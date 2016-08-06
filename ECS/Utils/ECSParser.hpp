#pragma once
#include "cocos2d.h"
#include "../../artemis/Artemis.h"
#include "../../Utils/pugixml.hpp"



namespace EntityParser {
	extern artemis::Entity* parseXmlnode(artemis::World* world, const pugi::xml_node &node);
	extern artemis::Entity* parseFromFile(artemis::World* world, const std::string &file);
};

namespace ComponentParser {
	void setupDelegates();
	extern  artemis::Component* parseXmlnode(const pugi::xml_node &node);	
};

class ECSParser {
public:
	static ECSParser* getInstance();
	void parse(artemis::World* world, const std::string &filename);
	artemis::Entity* parseEntity(artemis::World* world, const std::string &filename);
private:
	ECSParser();

};



