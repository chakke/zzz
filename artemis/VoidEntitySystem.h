#ifndef ENT_VOID_SYS_H
#define ENT_VOID_SYS_H

#include "ImmutableBag.h"
#include "EntitySystem.h"

namespace artemis {

	class Entity;
  /**
   * @brief A typical entity system.
   *
   * Use this when you need to process entities possessing the provided 
   * component types.
   */
	class VoidEntitySystem : public EntitySystem {

		protected:
			VoidEntitySystem() {};			
			virtual void process() = 0;
			virtual void processEntity(Entity &e);
			virtual void processEntities(ImmutableBag<Entity*> & bag);
			virtual bool checkProcessing();
	};
};

#endif // $(Guard token)
