#include "RenderComponent.hpp"

RenderComponent::RenderComponent(float delayTime) : artemis::Component()
{
	mView = cocos2d::Node::create();
	mView->setAnchorPoint(cocos2d::Vec2(.5f, .5f));
	mView->ignoreAnchorPointForPosition(false);

	mLayer = 0;
	mDelayTime = delayTime;
	mLinked = false;
	CC_SAFE_RETAIN(mView);
}

RenderComponent::~RenderComponent() {
	CC_SAFE_RELEASE_NULL(mView);
}


cocos2d::Node * RenderComponent::getView()
{
	return mView;
}

void RenderComponent::setView(cocos2d::Node * node)
{
	mView = node;
}

int RenderComponent::getLayer()
{
	return mLayer;
}

void RenderComponent::setLayer(int layer)
{
	this->mLayer = layer;
	auto parent = getView()->getParent();
	if (parent) {
		if (parent->getLocalZOrder() == layer) return;
		getView()->removeFromParent();
		linkTo(parent);
	}
}

float RenderComponent::getDelayTime()
{
	return mDelayTime;
}

void RenderComponent::setDelayTime(float time)
{
	this->mDelayTime = time;
}

bool RenderComponent::isLinked()
{
	return mLinked;
}

void RenderComponent::linkTo(cocos2d::Node * parent)
{
	if (!parent->getChildByTag(mLayer)) {
		auto node = cocos2d::Node::create();
		node->setTag(mLayer);
		node->setLocalZOrder(mLayer);
		parent->addChild(node);
	}
	auto layer = parent->getChildByTag(mLayer);
	if (!getView()) return;
	if (getView()->getParent()) getView()->removeFromParent();
	layer->addChild(getView());
	mLinked = true;
}


