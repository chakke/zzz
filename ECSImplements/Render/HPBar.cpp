#include "HPBar.hpp"
#include "../../UIParser/Atlas/AtlasCache.hpp"
#include "../../Config/GameConstants.hpp"
HPBar::HPBar()
{
	mContentSize = cocos2d::Size(100, 20);
	mRenderNode = cocos2d::Node::create();
	mBorder = CustomUIImageView::create();
	mBorder->setSpriteFrame(atlas_cache::getSpriteFrame("atlas/game_ui.plist", "border.png"));
	mNinePatch = CustomUIImageView::create();
	mNinePatch->setSpriteFrame(atlas_cache::getSpriteFrame("atlas/game_ui.plist", "box.png"));


	mRenderNode->addChild(mNinePatch);
	mRenderNode->addChild(mBorder);

	mBorder->setAnchorPoint(cocos2d::Vec2(.5f, .5f));
	mNinePatch->setAnchorPoint(cocos2d::Vec2(0, .5f));
	mNinePatch->setScale9Enabled(true);

	mBorder->setScale9Enabled(true);
	mBorder->setCapInsets(cocos2d::Rect(2, 2, 36, 36));
	mNinePatch->setCapInsets(cocos2d::Rect(0, 2, 40, 36));

	setContentSize(mContentSize);
	setPercent(1);

	this->mFree = true;
	CC_SAFE_RETAIN(mRenderNode);
}

HPBar::~HPBar()
{
	CC_SAFE_RELEASE_NULL(mRenderNode);
}

void HPBar::setPercent(float percent, bool visible)
{
	mPercent = percent;
	mNinePatch->setContentSize(cocos2d::Size(mContentSize.width*percent, mContentSize.height));
	mRenderNode->setVisible(visible);
}

void HPBar::onCreate(int playSide, const float percent)
{
	this->mPercent = percent;
	this->mBorder->setColor(cocos2d::Color3B::BLACK);
	if (playSide == game::side::SIDE_1) {
		this->mNinePatch->setColor(cocos2d::Color3B::BLUE);
	}
	else if (playSide == game::side::SIDE_2) {
		this->mNinePatch->setColor(cocos2d::Color3B::RED);
	}
	else if (playSide == game::side::SIDE_3) {
		this->mNinePatch->setColor(cocos2d::Color3B::GREEN);
	}
	else if (playSide == game::side::SIDE_4) {
		this->mNinePatch->setColor(cocos2d::Color3B::BLACK);
	}
}

void HPBar::setVisible(bool visible)
{
	this->mRenderNode->setVisible(visible);
}

void HPBar::setPlaySide(int playSide)
{
	if (playSide == game::side::SIDE_1) {
		this->mNinePatch->setColor(cocos2d::Color3B::BLUE);
	}
	else if (playSide == game::side::SIDE_2) {
		this->mNinePatch->setColor(cocos2d::Color3B::RED);
	}
	else if (playSide == game::side::SIDE_3) {
		this->mNinePatch->setColor(cocos2d::Color3B::GREEN);
	}
	else if (playSide == game::side::SIDE_4) {
		this->mNinePatch->setColor(cocos2d::Color3B::BLACK);
	}
}

void HPBar::setContentSize(cocos2d::Size size)
{
	this->mContentSize = size;
	this->mBorder->setContentSize(size);
	this->mNinePatch->setContentSize(cocos2d::Size(size.width* this->mPercent, size.height));
	this->mBorder->setPosition(cocos2d::Vec2(0, 0));
	this->mNinePatch->setPosition(cocos2d::Vec2(-mContentSize.width / 2, 0));

}

void HPBar::free()
{
	if (mRenderNode->getParent()) mRenderNode->removeFromParent();
	this->setVisible(false);
	this->mFree = true;
}

void HPBar::enableBorder(bool enable)
{
	mBorder->setVisible(enable);
}

void HPBar::obtain(int playSide, cocos2d::Size size, float percent)
{
	
	this->setContentSize(size);
	this->setPlaySide(playSide);
	this->setPercent(percent);
	this->setVisible(true);
	this->mFree = false;
	this->mBorder->setColor(cocos2d::Color3B::BLACK);
	this->mBorder->setOpacity(80);
}

cocos2d::Node * HPBar::getView()
{
	return mRenderNode;
}
