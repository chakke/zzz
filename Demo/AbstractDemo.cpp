#include "AbstractDemo.hpp"

#include "../ECS/GameConfig.hpp"
#include "../ECS/Component/Components.hpp"
#include "../ECS/System/Systems.h"
#include "../ECS/Entity/EntityUtils.hpp"
#include "../ECSImplements/System/ISystems.h"
#include "../ECSImplements/Component/IComponents.hpp"
#include "../Core/Animations/SpineAnimation.hpp"
#include "../Core/Animations/SpriteAnimation.hpp"

#include "../Network/AppConnectorConfig.hpp"
#include "../Game/Controller/ToastController.hpp"
#include "../Core/Command/CommandDispatcher.hpp"
#include "../Core/Command/Commands.hpp"
#include "../Config/GameConstants.hpp"
#include "../UIParser/CustomUI/CustomUIImageView.hpp"
#include "../UIParser/Atlas/AtlasCache.hpp"
#include "../ECS/Utils/ECSParser.hpp"

USING_NS_CC;

AbstractDemo::AbstractDemo() : AbstractGame() {}
AbstractDemo::~AbstractDemo() {}
void AbstractDemo::onAdded()
{
	CommandDispatcher::getInstance()->unRegisterAll();
	CommandDispatcher::getInstance()->registerObserver(this);
}
void AbstractDemo::onRemoved() {
	CommandDispatcher::getInstance()->unRegisterObserver(getObserverID());
	CommandDispatcher::getInstance()->unRegisterObserver(mCameraManager->getObserverID());
	cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(mGameLayout, true);

	getGameLayout()->removeAllChildren();
	getBackgroundLayout()->removeAllChildren();
	getHudLayout()->removeAllChildren();

	getGameLayout()->removeFromParent();
	getBackgroundLayout()->removeFromParent();
	getHudLayout()->removeFromParent();
}

void AbstractDemo::process(float delta) {
	AbstractGame::process(delta);
	if (mCameraManager) mCameraManager->process(delta);
}

void AbstractDemo::initGameLayout(cocos2d::Size worldSize, cocos2d::Node* parent) {

	cocos2d::Size designSize = game::config->getViewportSize();
	float width = cocos2d::Director::getInstance()->getOpenGLView()->getDesignResolutionSize().width;
	float height = cocos2d::Director::getInstance()->getOpenGLView()->getDesignResolutionSize().height;
	float STRETCH_SCALE = MIN(width / designSize.width, height / designSize.height);

	mBackgroundLayout->setContentSize(cocos2d::Size(width, height));

	mGameLayout->setContentSize(worldSize);
	mGameLayout->setPosition(cocos2d::Vec2(-worldSize.width / 2, -worldSize.height / 2));
	mGameLayout->ignoreAnchorPointForPosition(true);
	mGameLayout->setScale(STRETCH_SCALE);

	mHudLayout->setContentSize(cocos2d::Size(width, height));

	parent->addChild(mBackgroundLayout);
	parent->addChild(mGameLayout);
	parent->addChild(mHudLayout);

}
void AbstractDemo::createWorld() {
	getBackgroundLayout()->removeAllChildren();
	getHudLayout()->removeAllChildren();
	getGameLayout()->removeAllChildren();
	mCameraManager = new CameraManager(getGameLayout());
	mTouchManager = new TouchManager();
	mTouchManager->createTouch(getGameLayout());
	CommandDispatcher::getInstance()->registerObserver(mCameraManager);

	this->loadSystemAndConfig();
	this->loadEntities();
}
void AbstractDemo::loadSystemAndConfig()
{
	game::config->setPlayerID(1);
	game::config->setPlaySide(game::side::SIDE_1);
	game::config->setEnemySide(game::side::SIDE_2);
	game::config->setMapType(game::map::SPRING);
	game::config->setBlockInput(false);

	addSystem(new AnimationSystem());
	addSystem(new AfterPhysicSystem());
	addSystem(new AnimationSystem());
	addSystem(new RemoveEntitySystem());
	addSystem(new VelocityDrawSystem());
	addSystem(new RenderSystem(getGameLayout()));
	addSystem(new SortRenderSystem());

	mWorld->getSystemManager()->initializeAll();
}
artemis::EntitySystem*  AbstractDemo::addSystem(artemis::EntitySystem* system) {
	return mWorld->getSystemManager()->setSystem(system);
}

void AbstractDemo::onRecieveCommand(int type, std::shared_ptr<connection_object> data) {

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


void AbstractDemo::onGlobalTouchMove(std::shared_ptr<connection_object> data) {
	if (game::config->isBlockInput()) return;
	cocos2d::Vec2 pos(data->getFloat("x"), data->getFloat("y"));
	cocos2d::Vec2 delta(data->getFloat("dx"), data->getFloat("dy"));

	pos = getGameLayout()->convertToNodeSpace(pos);
	delta = getGameLayout()->convertToNodeSpace(delta);

	sendCommand(command::ON_MOVE_GAME_CAMERA, data);
}
void AbstractDemo::onGlobalTouchEnd(std::shared_ptr<connection_object> data) {
	if (game::config->isBlockInput()) return;
	cocos2d::Vec2 pos(data->getFloat("x"), data->getFloat("y"));
	pos = getGameLayout()->convertToNodeSpace(pos);

}

void AbstractDemo::onGlobalTouchZoom(std::shared_ptr<connection_object> data) {
	if (game::config->isBlockInput()) return;
	sendCommand(command::ON_ZOOM_CAMERA, data);
}
void AbstractDemo::onGlobalTouchFling(std::shared_ptr<connection_object> data) {
	if (game::config->isBlockInput()) return;
	sendCommand(command::ON_FLING_GAME_CAMERA, data);
}

cocos2d::Vec2 AbstractDemo::convertToGameSpace(cocos2d::Vec2 pos)
{
	return getGameLayout()->convertToNodeSpace(pos);
}


void AbstractDemo::onGlobalTap(std::shared_ptr<connection_object> data) {
	if (game::config->isBlockInput()) return;
}

void AbstractDemo::loadEntities() {
	/*create background*/
	{
		auto map = cocos2d::experimental::TMXTiledMap::create(cocos2d::StringUtils::format("maps/map-%d.tmx",game::config->getMapType()));
		map->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
		map->setPosition(getGameLayout()->getContentSize() / 2);
		getGameLayout()->addChild(map);
	}
}
