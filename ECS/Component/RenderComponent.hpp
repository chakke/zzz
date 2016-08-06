#pragma once

#include "cocos2d.h"
#include "../../artemis/Component.h"
#include "ui/UILayout.h"
class RenderComponent : public artemis::Component {

public:
	RenderComponent(const float delayAdd = 0);
	~RenderComponent();
	cocos2d::Node*	getView();
	virtual void	setView(cocos2d::Node* node);
	
	int		getLayer();
	void	setLayer(int layer);

	float	getDelayTime();
	void	setDelayTime(float time);
	bool	isLinked();
	void	linkTo(cocos2d::Node* parent);
protected:
	int				mLayer;	
	bool			mLinked;
	float			mDelayTime;
	cocos2d::Node*	mView;
};
