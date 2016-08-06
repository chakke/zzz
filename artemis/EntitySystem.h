#ifndef ENTITY_SYSTEM_H
#define ENTITY_SYSTEM_H

#include <bitset>
#include "BitSize.h"
#include "Component.h"
#include <iostream>
#include <assert.h>
#include <typeinfo>
#include <bitset>
#include "ImmutableBag.h"
#include "Entity.h"
#include "ComponentTypeManager.h"


namespace artemis {
  
	class Entity;
	class World;
  
	/**
   * The most raw entity system. It should not typically be used, but you can create your own
   * entity system handling by extending this. It is recommended that you use the other provided
   * entity system implementations.
   */

	enum SystemType{
	PASSIVE,NONE_PASSIVE
	};

	class EntitySystem {
  public:
    void printTypeFlag() {
      std::cout << typeFlags;
    }
    std::bitset<BITSIZE> getSystemBit() {
      return systemBit;
    }
	template<typename component_type>
	component_type* getComponent(artemis::Entity &e) {
		return (component_type*)(e.getComponent<component_type>());
	};
	virtual void setSystemType(SystemType sytemType);
	virtual SystemType getSystemType();
    void setSystemBit(std::bitset<BITSIZE> bit);
    virtual ~EntitySystem();
    /*override these functions*/
    virtual void initialize() {};
    void setWorld(World *world);
    void change(Entity &e);
    void process();
    int getEntityCount();
  protected:
    EntitySystem() { this->world = NULL; 
	type = NONE_PASSIVE;
	};
    World * world;
    /**
     * Call this in the constructor of the derived system
     */
    template<typename component_type>
    void addComponentType() {
      //Add Bits to typeflags
      typeFlags |= ComponentTypeManager::getBit<component_type>();
	}
	
    /*override these functions*/
    virtual void begin() {};
    virtual void end() {};
    virtual void removed(Entity &e) {};
    virtual void added(Entity &e) {};
    //Abstracts
    virtual void processEntities(ImmutableBag<Entity*> & bag) = 0;
    virtual bool checkProcessing() = 0;
  private:
	SystemType type;
    std::bitset<BITSIZE> systemBit;
    std::bitset<BITSIZE> typeFlags;
    Bag<Entity*> actives;
    void remove(Entity &e);
	};
  
};


#endif
