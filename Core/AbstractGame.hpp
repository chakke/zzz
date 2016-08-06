#pragma once
#include "cocos2d.h"
#include "Command/CommandObserver.hpp"
#include "ui/CocosGUI.h"
#include "../artemis/Artemis.h"
class AbstractGame : public CommandObserver {
public:
	enum class GameState {
		NONE, RUNNING,PAUSE, DISPOSE
	};
	AbstractGame();
	~AbstractGame();

	virtual void onAdded();
	virtual void onRemoved();

	virtual void process(float delta);
	virtual void setTimeScale(float timeScale);
	virtual void setGameState(GameState state);
	virtual void setTimeOnState(float delta);

	virtual float getTimeOnState();
	virtual float getTimeScale();
	virtual GameState getGameState();

	virtual cocos2d::ui::Layout* getGameLayout();
	virtual cocos2d::ui::Layout* getHudLayout();
	virtual cocos2d::ui::Layout* getBackgroundLayout();
	virtual void initGameLayout(cocos2d::Size worldSize, cocos2d::Node* parent) = 0;	
	virtual void onRecieveCommand(int commandTag, std::shared_ptr<connection_object> data);
	virtual void createWorld() = 0;
protected:

	GameState mState;
	float mTimeOnState;
	float mTimeScale;

	artemis::World* mWorld;
	float mWorldAccumulate;
	float WORLD_STEP;	

	cocos2d::ui::Layout* mGameLayout;
	cocos2d::ui::Layout* mHudLayout;
	cocos2d::ui::Layout* mBackgroundLayout;

	template<typename component_type>
	component_type* getComponent(artemis::Entity* e) {
		return (component_type*)e->getComponent<component_type>();
	};
};
