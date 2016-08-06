
#include "AbstractGame.hpp"

AbstractGame::AbstractGame() : mState(GameState::NONE), mTimeOnState(0), mTimeScale(1) {
	mGameLayout = cocos2d::ui::Layout::create();
	mHudLayout = cocos2d::ui::Layout::create();
	mBackgroundLayout = cocos2d::ui::Layout::create();

	mGameLayout->setAnchorPoint(cocos2d::Vec2(.5f, .5f));
	mHudLayout->setAnchorPoint(cocos2d::Vec2(.5f, .5f));
	mBackgroundLayout->setAnchorPoint(cocos2d::Vec2(.5f, .5f));

	mWorld = new artemis::World();
	WORLD_STEP = 0.015f;
	mWorldAccumulate = 0;

	CC_SAFE_RETAIN(mGameLayout);
	CC_SAFE_RETAIN(mHudLayout);
	CC_SAFE_RETAIN(mBackgroundLayout);
}
AbstractGame::~AbstractGame() {
	CC_SAFE_RELEASE_NULL(mGameLayout);
	CC_SAFE_RELEASE_NULL(mHudLayout);
	CC_SAFE_RELEASE_NULL(mBackgroundLayout);
}
void AbstractGame::onAdded()
{
}
void AbstractGame::onRemoved()
{
}
cocos2d::ui::Layout* AbstractGame::getGameLayout() {
	return mGameLayout;
}
cocos2d::ui::Layout* AbstractGame::getHudLayout() {
	return mHudLayout;
}
cocos2d::ui::Layout* AbstractGame::getBackgroundLayout() {
	return mBackgroundLayout;
}
void AbstractGame::process(float delta)
{
	this->mTimeOnState += delta;	
	if (mWorld) {
		mWorldAccumulate += delta;
		while (mWorldAccumulate >= WORLD_STEP) {
			mWorld->setDelta(WORLD_STEP);
			mWorld->loopStart();
			mWorld->processWorld();
			mWorldAccumulate -= WORLD_STEP;
		}
	}	
}
void AbstractGame::setTimeScale(float timeScale) { this->mTimeScale = timeScale; }

void AbstractGame::setGameState(GameState state) { this->mState = state; setTimeOnState(0); }

void AbstractGame::setTimeOnState(float time) { this->mTimeOnState = time; }

AbstractGame::GameState AbstractGame::getGameState() { return mState; }

float AbstractGame::getTimeScale() { return mTimeScale; }

float AbstractGame::getTimeOnState() { return mTimeOnState; }
void AbstractGame::createWorld() {}

void AbstractGame::onRecieveCommand(int commandTag, std::shared_ptr<connection_object> data) {
	CommandObserver::onRecieveCommand(commandTag, data);
}



