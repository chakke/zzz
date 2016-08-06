#pragma once
#include "../../artemis/Artemis.h"
#include "../../Data/ConnectionData.hpp"
class EffectSystem : public artemis::VoidEntitySystem
{
public:
	EffectSystem();
	virtual void process();
	virtual void showEffectAttack(std::shared_ptr<connection_object> data);
	virtual void showEffectShield(std::shared_ptr<connection_object> data);
protected:	
	
};

