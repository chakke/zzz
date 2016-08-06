#pragma once
#include "../../artemis/Artemis.h"
#include "../../Core/Maps/Graph.hpp"
class MapSystem : public artemis::DelayedEntityProcessingSystem
{
public:
	MapSystem();	
	virtual void begin();
	virtual void initialize();	
	virtual void processEntities(artemis::ImmutableBag<artemis::Entity*>& bag, float accumulatedDelta);
	virtual void processEntity(artemis::Entity& e, float accumulatedDelta);	
	virtual void addMapMask(int playSide, Graph* mapMask);
	virtual Graph* getMapMask(int playSide);
	virtual void addCustomMask(int type,Graph* graph);
	virtual Graph* getCustomMask(int type);
	virtual std::vector<int> getEntitiesAroundPosition(cocos2d::Vec2 position, int playSide);
	virtual std::vector<int> getEntitiesInPosition(cocos2d::Vec2 position, int playSide);
	virtual std::vector<int> getEntitiesInRange(cocos2d::Vec2 position,float rw,float rh, int playSide);
protected:	
	std::map<int, Graph*> _maps;
	std::map<int, Graph*> _custom_maps;	
};

