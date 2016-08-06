
#include "LoadingViewController.hpp"
#include "../../UIParser/UIParser.hpp"
#include "../../UIParser/Atlas/AtlasCache.hpp"
#include "../../Core/GameAnimations.hpp"
#include "../../Config/FixedData.hpp"
#include "../../ECS/GameConfig.hpp"
#include "ui/UIImageView.h"

#include "../../UIParser/CustomUI/CustomUIData.h"
#include "../../UIParser/CustomUI/CustomUIImageView.hpp"



bool LoadingViewController::init()
{
	_callback = nullptr;

	auto node = UIParser::parse("xml/loading.xml");
	setView(node);

	_loadingSuccess = false;
	mStartLoading = false;

	{
		auto customUIData = dynamic_cast<CustomUIData*>(node);
		auto rootParser = (UIParser*)customUIData->getCustomUIData().at(0);


		auto background = cocos2d::ui::ImageView::create("texture/loading/background_loading.png");
		auto visibleSize = cocos2d::Director::getInstance()->getWinSize();
		background->setAnchorPoint(cocos2d::Vec2(.5f, .5f));
		background->setScaleX(visibleSize.width / background->getContentSize().width);
		background->setScaleY(visibleSize.height / background->getContentSize().height);
		background->setScale9Enabled(true);


		auto logoGame = cocos2d::ui::ImageView::create("texture/loading/logogame.png");
		logoGame->setAnchorPoint(cocos2d::Vec2(.5f, .5f));
		logoGame->setPosition(cocos2d::Vec2(0, -60 + logoGame->getContentSize().height / 2));

		auto bgLoading = cocos2d::ui::ImageView::create("texture/loading/loading.png");
		bgLoading->setAnchorPoint(cocos2d::Vec2(.5f, .5f));
		bgLoading->setPosition(cocos2d::Vec2(0, -200 + bgLoading->getContentSize().height / 2));

		mLoadingKnob = cocos2d::ui::ImageView::create("texture/loading/loading_dot.png");
		mLoadingKnob->setAnchorPoint(cocos2d::Vec2(0, .5f));
		mLoadingKnob->setPosition(cocos2d::Vec2(bgLoading->getPositionX() - bgLoading->getContentSize().width / 2 + 25, bgLoading->getPositionY()));
		mLoadingKnob->setScale9Enabled(true);
		mLoadingKnob->setCapInsets(cocos2d::Rect(10, 0, 20, 31));
		mLoadingKnob->setScaleY(0.9f);
		mLoadingKnob->setContentSize(cocos2d::Size(0, mLoadingKnob->getContentSize().height));

		mLoadingSword = cocos2d::ui::ImageView::create("texture/loading/sword.png");
		mLoadingSword->setAnchorPoint(cocos2d::Vec2(0.5f, .5f));
		mLoadingSword->setPosition(cocos2d::Vec2(mLoadingKnob->getPositionX(), mLoadingKnob->getPositionY()));

		mLbPercent = cocos2d::Label::createWithBMFont("fonts/font-ingame.fnt", "0%", cocos2d::TextHAlignment::CENTER, 300);
		mLbPercent->setAnchorPoint(cocos2d::Vec2(.5f, 0.5f));
		mLbPercent->setPosition(cocos2d::Vec2(0, bgLoading->getPositionY() + mLoadingKnob->getContentSize().height));

		auto parent = rootParser->getHasNodes()->at("layout_background");
		parent->addChild(background);
		parent->addChild(logoGame);
		parent->addChild(bgLoading);
		parent->addChild(mLoadingKnob);
		parent->addChild(mLoadingSword);
		parent->addChild(mLbPercent);

	}

	return true;
}

void LoadingViewController::onRemove()
{
	unscheduleUpdate();
}

void LoadingViewController::onLinked()
{
	scheduleUpdate();
	getView()->runAction(cocos2d::Sequence::create(cocos2d::DelayTime::create(.1f), cocos2d::CallFunc::create([=]() { loadAtlas(); }), nullptr));
}

void LoadingViewController::loadAtlas() {

	pushStep(18, [=]() {   
		game::setupConfig(); 
		FixedData::getInstance();
	});
	pushStep(44, [=]() {
		atlas_cache::reserve("atlas/login.plist");
		atlas_cache::reserve("atlas/levels.plist");
		atlas_cache::reserve("atlas/troop-1.plist");
	});

	pushStep(73, [=]() {
		atlas_cache::reserve("atlas/troop-2.plist");
		/*		
		atlas_cache::reserve("atlas/troop-3.plist");
		atlas_cache::reserve("atlas/troop-4.plist");
		*/
		atlas_cache::reserve("atlas/game_ui.plist");
		atlas_cache::reserve("atlas/choice_room.plist");
		atlas_cache::reserve("atlas/actors.plist");
	});
	pushStep(100, [=]() {
		game::GameAnimations::getInstance()->loadAnimations();
	});

	finishLoading();
}

void LoadingViewController::setOnLoadingViewCallback(const LoadingViewCallback& callback)
{
	_callback = callback;
}

static float timeLoading = 0;
void LoadingViewController::update(float delta)
{
	if (!_loadingSuccess) {
		if (mStartLoading) {
			if (mPercent < mTarget) mPercent += 1; else nextStep();
			updateProgress();
		}
	}
}
void LoadingViewController::pushStep(int percent, const std::function<void()>& function)
{
	_steps.push_back(loading::LoadingStep(percent, function));
}
void LoadingViewController::finishLoading()
{
	mStartLoading = true;
	_loadingSuccess = false;
	mPercent = 0;
	nextStep();
}
void LoadingViewController::nextStep()
{
	if (_steps.size() > 0) {
		auto step = _steps.at(0);
		mTarget = step.mPercent;
		step.mFunction();
		_steps.erase(_steps.begin());
	}
	else {
		// load done			
		_loadingSuccess = true;
		getView()->runAction(cocos2d::Sequence::create(cocos2d::DelayTime::create(.1f), cocos2d::CallFunc::create([=]() {
			if (_callback) {
				_callback();
			}
		}), nullptr));
	}
}
void LoadingViewController::updateProgress()
{
	if (_loadingSuccess) {
		float width = 455;
		mLoadingKnob->setContentSize(cocos2d::Size(width, mLoadingKnob->getContentSize().height));
		mLoadingSword->setPosition(cocos2d::Vec2(mLoadingKnob->getPositionX() + width, mLoadingKnob->getPositionY()));
		mLbPercent->setString("100%");
		return;
	}
	int percentInt = (int)mPercent;
	percentInt = MAX(percentInt, 0);
	percentInt = MIN(percentInt, 100);
	float width = percentInt * 455 / 100.0f;
	mLoadingKnob->setContentSize(cocos2d::Size(width, mLoadingKnob->getContentSize().height));
	mLoadingSword->setPosition(cocos2d::Vec2(mLoadingKnob->getPositionX() + width, mLoadingKnob->getPositionY()));
	mLbPercent->setString(cocos2d::StringUtils::format("%d%s", percentInt, "%").c_str());

}


