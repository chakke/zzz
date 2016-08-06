#pragma once
#include "cocos2d.h"
#include "../../artemis/Artemis.h"
#include "../../Data/ConnectionData.hpp"
class EntityUtils {
public:
	static EntityUtils* getInstance();
//	cocos2d::Vec2 generateTroopPosition(cocos2d::Vec2 castlePosition, int troop_index, int type);
	std::vector<artemis::Entity*> getCastleTroops(artemis::World* world, int castleID, int playSide, int type);
	std::vector<artemis::Entity*> getAllCastleTroops(artemis::World* world, int castleID);
	std::vector<artemis::Entity*> getTroopsInTransfer(artemis::World* world, int playSide, int transferID);


	artemis::Entity* createTroopEntity(artemis::World* world, std::shared_ptr<connection_object> data);
	artemis::Entity* createCastle(artemis::World* world, std::shared_ptr<connection_object> data);
	artemis::Entity* createBuilder(artemis::World* world, std::shared_ptr<connection_object> data);
	artemis::Entity* createEffectAttack(artemis::World* world, std::shared_ptr<connection_object> data);
	artemis::Entity* createEffectSafe(artemis::World* world, std::shared_ptr<connection_object> data);
private:
	EntityUtils();

};



