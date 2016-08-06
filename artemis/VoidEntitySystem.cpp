#include "Artemis/VoidEntitySystem.h"

namespace artemis {	
	void VoidEntitySystem::process() {	}
	void VoidEntitySystem::processEntity(Entity & e)
	{
	}
	void VoidEntitySystem::processEntities(ImmutableBag<Entity*>& bag)
	{
		if (checkProcessing()) {
			process();
		}
	}
	bool VoidEntitySystem::checkProcessing()
	{
		return true;
	}
};
