
#include "EntityUtils.hpp"
#include "../../Core/Math/Vector2.hpp"
#include "../../Core/Animations/SpriteAnimation.hpp"

#include "../../Config/GameConstants.hpp"
#include "../../Config/FixedData.hpp"
#include "../GameConfig.hpp"
#include "../Component/Components.hpp"
#include "../../ECSImplements/Component/IComponents.hpp"

#include "ui/CocosGUI.h"
#include <spine/spine-cocos2dx.h>
EntityUtils* _ins = nullptr;

EntityUtils::EntityUtils() {}

EntityUtils * EntityUtils::getInstance()
{
	if (!_ins) _ins = new EntityUtils();
	return _ins;
}

std::vector<artemis::Entity*> EntityUtils::getCastleTroops(artemis::World * world, int castleID, int playSide, int type)
{
	std::vector<artemis::Entity*> results;
	std::string group = cocos2d::StringUtils::format("troops_%d", playSide).c_str();
	auto list = world->getGroupManager()->getEntities(group);
	for (int i = 0; i < list->getCount(); i++) {
		auto e = list->get(i);
		auto idComponent = (IDComponent*)(e->getComponent<IDComponent>());
		if (idComponent->getID(game::entity::CASTLE) == castleID) {
			if (type == -1)	results.push_back(e);
			else {
				auto typeComponent = (TypeComponent*)(e->getComponent<TypeComponent>());
				if (typeComponent->getType(game::entity::TROOP) == type)results.push_back(e);
			}
		}
	}

	return results;
}

std::vector<artemis::Entity*> EntityUtils::getAllCastleTroops(artemis::World * world, int castleID)
{
	std::vector<artemis::Entity*> results;

	for (int type = 0; type < 4; type++) {
		std::string group = cocos2d::StringUtils::format("troops_%d", type).c_str();
		auto list = world->getGroupManager()->getEntities(group);
		for (int i = 0; i < list->getCount(); i++) {
			auto e = list->get(i);
			auto idComponent = (IDComponent*)(e->getComponent<IDComponent>());
			if (idComponent->getID(game::entity::CASTLE) == castleID) {
				results.push_back(e);
			}
		}
	}
	return results;
}
std::vector<artemis::Entity*> EntityUtils::getTroopsInTransfer(artemis::World * world, int playerID, int transferID)
{
	std::vector<artemis::Entity*> results;
	std::string group = cocos2d::StringUtils::format("troops_%d", game::config->getType(playerID)).c_str();

	auto list = world->getGroupManager()->getEntities(group.c_str());
	for (int i = 0; i < list->getCount(); i++) {
		auto e = list->get(i);
		auto idComponent = (IDComponent*)(e->getComponent<IDComponent>());
		if (idComponent->getID(game::entity::TRANSFER) == transferID) {
			results.push_back(e);
		}
	}
	return results;
}

artemis::Entity* EntityUtils::createTroopEntity(artemis::World* world, std::shared_ptr<connection_object> data) {

	
	return nullptr;
}

artemis::Entity * EntityUtils::createCastle(artemis::World * world, std::shared_ptr<connection_object> data)
{

	return nullptr;
}

artemis::Entity * EntityUtils::createBuilder(artemis::World * world, std::shared_ptr<connection_object> data)
{


	return nullptr;
}

artemis::Entity * EntityUtils::createEffectAttack(artemis::World * world, std::shared_ptr<connection_object> data)

{

	return nullptr;

}

artemis::Entity * EntityUtils::createEffectSafe(artemis::World * world, std::shared_ptr<connection_object> data)
{
	return nullptr;
}

