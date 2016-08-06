#include "BuildSystem.h"
#include "../../Data/ConnectionData.hpp"
#include "../../Config/GameConstants.hpp"
#include "../../ECS/Component/Components.hpp"
#include "../../ECSImplements/Component/IComponents.hpp"
#include "../../ECS/Entity/EntityUtils.hpp"
BuildSystem::BuildSystem()
{
	addComponentType<IDComponent>();
	addComponentType<PlaySideComponent>();
	addComponentType<BuilderComponent>();	
}

void BuildSystem::initialize()
{
	idMapper.init(*world);
	playSideMapper.init(*world);
	builderMapper.init(*world);
}

void BuildSystem::processEntity(artemis::Entity & e)
{
	auto builderComponent = builderMapper.get(e);
	if (!builderComponent->isActive()) return;
	int playSide = playSideMapper.get(e)->getSide();
	auto sideTroopContainer = getComponent<TroopContainerComponent>(world->getTagManager()->getEntity("troop_entity"));
	if (sideTroopContainer->getTotalTroop(playSide) >= sideTroopContainer->getCapacity()) return;
	if (builderComponent->update(world->getDelta())) {
		auto idComponent = idMapper.get(e);
		auto data = std::shared_ptr<connection_object>(new connection_object());
		int castleID = idComponent->getID(game::entity::CASTLE);	
		auto castleEntity = &world->getTagManager()->getEntity(cocos2d::StringUtils::format("castle_%d", castleID));
		auto troopContainer = getComponent<TroopContainerComponent>(*castleEntity);
		auto type = builderComponent->getType();
		data->putInt("side", playSide);
		data->putInt("castle_id", castleID);
		data->putInt("type", type);
		data->putInt("index", troopContainer->getTroop(playSide, type));
		EntityUtils::getInstance()->createTroopEntity(world, data);
		troopContainer->addTroop(playSide, type);
		builderComponent->startBuild();
	}
}
