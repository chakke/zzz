#pragma once
#include "../../AppController/Controller.hpp"
#include "ui/UIImageView.h"
typedef std::function<void()> LoadingViewCallback;
namespace loading {
	struct LoadingStep {
		std::function<void()> mFunction;
		int mPercent;
		LoadingStep(int percent, const std::function<void()> &function) {
			mPercent = percent;
			mFunction = function;
		}
	};
}

class LoadingViewController : public Controller
{
public:
    CREATE_FUNC(LoadingViewController);
    
    virtual bool init();
    
    virtual void onRemove();
    
    virtual void onLinked();
    
    virtual void update(float delta);
    
    void setOnLoadingViewCallback(const LoadingViewCallback& callback);

	
private:
	void pushStep(int percent,const std::function<void()> &function);
	void finishLoading();
	void nextStep();

	void updateProgress();
	void loadAtlas();
    LoadingViewCallback _callback;
    bool _loadingSuccess;
	bool mStartLoading;
	float mPercent;
	float mTarget;

	cocos2d::ui::ImageView* mLoadingKnob;
	cocos2d::ui::ImageView* mLoadingSword;
	cocos2d::Label* mLbPercent;
	std::vector<loading::LoadingStep> _steps;
};
