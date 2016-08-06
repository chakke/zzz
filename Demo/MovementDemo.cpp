#include "MovementDemo.hpp"

#include "../ECS/GameConfig.hpp"
#include "../ECS/Component/Components.hpp"
#include "../ECS/System/Systems.h"
#include "../ECS/Entity/EntityUtils.hpp"
#include "../ECSImplements/System/ISystems.h"
#include "../ECSImplements/Component/IComponents.hpp"

#include "../Core/Command/Commands.hpp"
#include "../Config/GameConstants.hpp"
#include "../Config/Cmd.hpp"
#include "../ECS/Utils/ECSParser.hpp"

USING_NS_CC;

MovementDemo::MovementDemo() : AbstractDemo() {}
MovementDemo::~MovementDemo() {}

void MovementDemo::onRecieveCommand(int type, std::shared_ptr<connection_object> data) {

	if (type == command::ON_GLOBAL_TAP) {
		this->onGlobalTap(data);
	}
	else if (type == command::ON_GLOBAL_TOUCH_MOVE) {
		this->onGlobalTouchMove(data);
	}
	else if (type == command::ON_GLOBAL_TOUCH_END) {
		this->onGlobalTouchEnd(data);
	}
	else if (type == command::ON_GLOBAL_FLING) {
		this->onGlobalTouchFling(data);
	}
	else if (type == command::ON_GLOBAL_ZOOM) {
		this->onGlobalTouchZoom(data);
	}
}

void MovementDemo::onGlobalTap(std::shared_ptr<connection_object> data)
{
	if (game::config->isBlockInput()) return;

}

void MovementDemo::loadEntities()
{
	/*create background*/
	{
		auto map = cocos2d::experimental::TMXTiledMap::create(cocos2d::StringUtils::format("maps/map-%d.tmx", game::config->getMapType()));
		map->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
		map->setPosition(getGameLayout()->getContentSize() / 2);
		getGameLayout()->addChild(map);
	}
	ECSParser::getInstance()->parse(mWorld, "xml/demo/movement-demo-entities.xml");
	
}

void MovementDemo::loadSystemAndConfig()
{
	game::config->setPlayerID(1);
	game::config->setPlaySide(game::side::SIDE_1);
	game::config->setEnemySide(game::side::SIDE_2);
	game::config->setMapType(game::map::SPRING);
	game::config->setBlockInput(false);

	addSystem(new ActionSystem());
	addSystem(new AttackSystem());
	addSystem(new TroopSystem());
	addSystem(new MovementSystem());
	addSystem(new AnimationSystem());
	addSystem(new AfterPhysicSystem());
	addSystem(new AnimationSystem());
	addSystem(new RemoveEntitySystem());
	addSystem(new VelocityDrawSystem());
	addSystem(new RenderSystem(getGameLayout()));
	addSystem(new HPBarSystem());
	addSystem(new SortRenderSystem());

	mWorld->getSystemManager()->initializeAll();

	sendCommand(cmd::camera::ZOOM_TO, DataBuilder::builder()->putFloat("zoom", 1.2f)->putFloat("time", 1)->build());
}



