#pragma once

#include "../../ECS/Component/RenderComponent.hpp"
#include "ui/CocosGUI.h"

class BuilderComponent : public RenderComponent {

public:
	BuilderComponent();
	~BuilderComponent();
	void setType(int type);
	void setBuildTime(float time);
	void setEnable(bool enable);
	bool update(float delta);
	void startBuild();
	int getType();
	/*between 0 and 1*/	
	float getProgress();
	void setProgress(float progress);
protected:
	int mType;
	float mBuildTime;
	float mTime;
	bool mEnable;
};
