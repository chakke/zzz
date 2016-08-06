#include "Artemis/Component.h"
#include "Artemis/World.h"

namespace artemis {
	
  Component::~Component() {
    
  }

  bool Component::isDirty()
  {
	  return mDirty;
  }

  bool Component::isActive()
  {
	  return mActive;
  }

  void Component::setDirty(bool dirty)
  {
	  this->mDirty = dirty;

  }

  void Component::setActive(bool active)
  {
	  this->mActive = active;
  }
	
};
