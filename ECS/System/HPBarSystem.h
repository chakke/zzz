#pragma once
#include "../../artemis/Artemis.h"
#include "cocos2d.h"
#include "../../ECSImplements/Render/HPBar.hpp"
class HPBarSystem : public artemis::EntityProcessingSystem
{
public:
	HPBarSystem();
	void initialize();
	virtual void processEntity(artemis::Entity &e);		
	
private :
	void freeHPBar(artemis::Entity &e);
	void updateHPBar(artemis::Entity &e,float percent);

	HPBar* obtain();
	std::vector<HPBar*> _bars;
	std::map<int, HPBar*> _running_bars;
};

