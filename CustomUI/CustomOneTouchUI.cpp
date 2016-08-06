//
//  CustomOneTouchUI.cpp
//  FashionCat
//
//  Created by Manh Tran on 4/21/15.
//
//

#include "CustomOneTouchUI.h"
#include "ui/UIScale9Sprite.h"

USING_NS_CC;

CustomOneTouchListView::~CustomOneTouchListView()
{
    
}

bool CustomOneTouchListView::init()
{
    if (!ListView::init()) {
        return false;
    }
    _canHandleLogic = true;
    
    schedule([this](float delta){
        Size size = getContentSize();
        for (auto& p : getChildren()) {
            Vec2 bottomleft = convertToNodeSpace(p->convertToWorldSpace(Vec2::ZERO));
            Vec2 topright = convertToNodeSpace(p->convertToWorldSpace(Vec2(p->getContentSize())));
            if (bottomleft.x > size.width || topright.x < 0 || bottomleft.y > size.height || topright.y < 0) {
                p->setVisible(false);
            }
            else p->setVisible(true);
        }
    
    }, "checkout");
    return true;
}

void CustomOneTouchListView::handlePressLogic(cocos2d::Touch *touch)
{
    if(_canHandleLogic) ListView::handlePressLogic(touch);
}

void CustomOneTouchListView::handleMoveLogic(cocos2d::Touch *touch)
{
    if(_canHandleLogic) ListView::handleMoveLogic(touch);
}

void CustomOneTouchListView::handleReleaseLogic(cocos2d::Touch *touch)
{
    if(_canHandleLogic) ListView::handleReleaseLogic(touch);
}

bool CustomOneTouchListView::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unusedEvent)
{
    if (touch->getID() != 0) {
        return false;
    }
    
    return ListView::onTouchBegan(touch, unusedEvent);
}

void CustomOneTouchListView::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unusedEvent)
{
    if (touch->getID() != 0) {
        return;
    }
    
    ListView::onTouchMoved(touch, unusedEvent);
}

void CustomOneTouchListView::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unusedEvent)
{
    if (touch->getID() != 0) {
        return;
    }
    
    ListView::onTouchEnded(touch, unusedEvent);
}

void CustomOneTouchListView::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unusedEvent)
{
    if (touch->getID() != 0) {
        return;
    }
    
    ListView::onTouchCancelled(touch, unusedEvent);
}

void CustomOneTouchListView::interceptTouchEvent(cocos2d::ui::Widget::TouchEventType event,cocos2d::ui::Widget* sender,cocos2d::Touch* touch)
{
    ListView::interceptTouchEvent(event, sender, touch);
    if (_touchEnabled)
    {
        ui::Layout::interceptTouchEvent(event, sender, touch);
    }
}

//==========

CustomSeparateTouchLayout::CustomSeparateTouchLayout() : _touchID(-1), _callback(nullptr)
{
    
}

CustomSeparateTouchLayout::~CustomSeparateTouchLayout()
{
    
}

bool CustomSeparateTouchLayout::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unusedEvent)
{
    if (_touchID >= 0) {
        return false;
    }
    
    bool touched = Layout::onTouchBegan(touch, unusedEvent);
    
    if(touched)
    {
        _touchID = touch->getID();
    }
    return touched;
}

void CustomSeparateTouchLayout::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unusedEvent)
{
    if (touch->getID() != _touchID) {
        return;
    }
    
    Layout::onTouchMoved(touch, unusedEvent);
}

void CustomSeparateTouchLayout::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unusedEvent)
{
    if (touch->getID() != _touchID) {
        return;
    }
    _touchID = -1;
    
    Layout::onTouchEnded(touch, unusedEvent);
}

void CustomSeparateTouchLayout::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unusedEvent)
{
    if (touch->getID() != _touchID) {
        return;
    }
    _touchID = -1;
    
    Layout::onTouchCancelled(touch, unusedEvent);
}

void CustomSeparateTouchLayout::interceptTouchEvent(cocos2d::ui::Widget::TouchEventType event, cocos2d::ui::Widget* sender, cocos2d::Touch *touch)
{
    Layout::interceptTouchEvent(event, sender, touch);
    if (_callback) {
        _callback(event, sender, touch);
    }
}


CustomOneTouchPageView::~CustomOneTouchPageView()
{
    
}

bool CustomOneTouchPageView::init()
{
    if (!PageView::init()) {
        return false;
    }
    return true;
}

bool CustomOneTouchPageView::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unusedEvent)
{
    if (touch->getID() != 0) {
        return false;
    }
    
    return PageView::onTouchBegan(touch, unusedEvent);
}

void CustomOneTouchPageView::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unusedEvent)
{
    if (touch->getID() != 0) {
        return;
    }
    
    PageView::onTouchMoved(touch, unusedEvent);
}

void CustomOneTouchPageView::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unusedEvent)
{
    if (touch->getID() != 0) {
        return;
    }
    
    PageView::onTouchEnded(touch, unusedEvent);
}

void CustomOneTouchPageView::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unusedEvent)
{
    if (touch->getID() != 0) {
        return;
    }
    
    PageView::onTouchCancelled(touch, unusedEvent);
}

//==========


CustomOneTouchLayout::CustomOneTouchLayout()
//: _testHit(false)
{
    
}

CustomOneTouchLayout::~CustomOneTouchLayout()
{
    
}

bool CustomOneTouchLayout::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unusedEvent)
{
    if (touch->getID() != 0) {
        return false;
    }

    return Layout::onTouchBegan(touch, unusedEvent);
}

void CustomOneTouchLayout::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unusedEvent)
{
    if (touch->getID() != 0) {
        return;
    }
    
    Layout::onTouchMoved(touch, unusedEvent);
}

void CustomOneTouchLayout::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unusedEvent)
{
    if (touch->getID() != 0) {
        return;
    }
    
    Layout::onTouchEnded(touch, unusedEvent);
}

void CustomOneTouchLayout::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unusedEvent)
{
    if (touch->getID() != 0) {
        return;
    }
    
    Layout::onTouchCancelled(touch, unusedEvent);
}

//=========

CustomOneTouchSprite* CustomOneTouchSprite::create(cocos2d::SpriteFrame* frame)
{
    auto ret = new CustomOneTouchSprite();
    ret->init(frame);
    ret->autorelease();
    return ret;
}

CustomOneTouchSprite::CustomOneTouchSprite() : _sprite(nullptr)
{
    
}

bool CustomOneTouchSprite::init(cocos2d::SpriteFrame* frame)
{
    if (!CustomOneTouchLayout::init()) {
        return false;
    }
    _sprite = ui::Scale9Sprite::createWithSpriteFrame(frame);
    addChild(_sprite);
    setContentSize(_sprite->getContentSize());
    _sprite->setPosition(getContentSize()/2);
    
    return true;
}

ui::Scale9Sprite* CustomOneTouchSprite::getSprite()
{
    return _sprite;
}

void CustomOneTouchSprite::setScale9Enable(const bool& scale9)
{
    _sprite->setScale9Enabled(scale9);
}

void CustomOneTouchSprite::setCap(const cocos2d::Rect& rect)
{
    _sprite->setCapInsets(rect);
}

void CustomOneTouchSprite::setContentSize(const cocos2d::Size& size)
{
    CustomOneTouchLayout::setContentSize(size);
    if(_sprite)
    {
        _sprite->setContentSize(size);
        _sprite->setPosition(getContentSize()/2);
    }
}

//==========


CustomOneTouchImageView* CustomOneTouchImageView::create(const std::string& image)
{
    auto *widget = new (std::nothrow) CustomOneTouchImageView;
    if (widget && widget->init(image)) {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}

CustomOneTouchImageView::CustomOneTouchImageView() : _autoReleaseTexture(false)
{
    
}

CustomOneTouchImageView::~CustomOneTouchImageView()
{
    
}

void CustomOneTouchImageView::setAutoReleaseTexture(bool flag)
{
    
}

bool CustomOneTouchImageView::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unusedEvent)
{
    if (touch->getID() != 0) {
        return false;
    }
    
    return ImageView::onTouchBegan(touch, unusedEvent);
}

void CustomOneTouchImageView::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unusedEvent)
{
    if (touch->getID() != 0) {
        return;
    }
    
    ImageView::onTouchMoved(touch, unusedEvent);
}

void CustomOneTouchImageView::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unusedEvent)
{
    if (touch->getID() != 0) {
        return;
    }
    
    ImageView::onTouchEnded(touch, unusedEvent);
}

void CustomOneTouchImageView::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unusedEvent)
{
    if (touch->getID() != 0) {
        return;
    }
    
    ImageView::onTouchCancelled(touch, unusedEvent);
}

//==============================

CustomScale9Sprite* CustomScale9Sprite::create(const std::string& file)
{
    auto ret = new CustomScale9Sprite();
    ret->initWithFile(file);
    ret->autorelease();
    return ret;
}