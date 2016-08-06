#pragma once

#include "../../AppController/Controller.hpp"
#include "../../Data/ObserverData.hpp"
#include "../../ECS/GameConfig.hpp"
#include "../../Core/Command/CommandObserver.hpp"
#include "../../UIParser/UIParser.hpp"
#include "ui/CocosGUI.h"
namespace hudcontroller {

	struct Ranger{
		float mValue;
		float mMin;
		float mMax;
		float mCurrent;
		float mThreshold;
		Ranger(float min, float max, float value) {
			mThreshold = .1f;
			mMin = min;
			mMax = max;
			mCurrent = value;
			mValue = value;
		}
		Ranger() {
			mThreshold = .1f;
			mMin = 0;
			mMax = 1;
			mCurrent = 0;
			mValue = 1;
		}
	};

	struct BuilderType :public cocos2d::Ref{
		int mType;
		int mPlayer;
		bool mLock;
		bool mNew;


		BuilderType(int type, bool isNew = false, bool lock = false) {
			//mPlayer = game::config->getType(game::config->getPlayerID());
			mPlayer = 0;
			mType = type;
			mNew = isNew;
			mLock = lock;
		}
	};
};

class HudController : public Controller, public CommandObserver
{
public:
	CREATE_FUNC(HudController);

    virtual bool init();
    
    virtual void onRemove();
    
    virtual void onLinked();
    
    virtual void update(float delta);
    
    virtual void listen(Observer* sender, cocos2d::Ref* ref);

	void onRecieveCommand(int commandTag, std::shared_ptr<connection_object> data);
	std::shared_ptr<connection_object> onMessage(int commandTag, std::shared_ptr<connection_object> data);
	void setBackCallback(const std::function<void()> &callback);
private :
	 void onTouchBack(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	 void onTouchBabarian(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	 void onTouchHorse(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	 void onTouchArcher(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);	 
	 void onTouchBuilder(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	void addBuilder(int type, bool isNew = false, bool isLocked = false);
	void showHud(bool show);
	void updateUINewMatch();
	

	float getPercent();
	void setPercent(float percent,const bool force = false);
	void updateRangerUI();
	void setTroopEnable(int troopType, bool enable);

	void showLayoutBuilders(bool show, const bool force = false);

	int mCastleID;
	

	hudcontroller::Ranger mRanger;
	std::vector<bool> _troops;	
	cocos2d::ui::ImageView* ninepatch;
	UIParser* mRootParser;	

	std::function<void()> _back_callback;
};


