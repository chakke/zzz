#pragma once

#include "cocos2d.h"
#include "ui/UIListView.h"
#include "ui/UIPageView.h"
#include "ui/UIImageView.h"
#include "ui/UIScale9Sprite.h"


typedef std::function<void(cocos2d::ui::Widget::TouchEventType event, cocos2d::ui::Widget* sender, cocos2d::Touch *touch)> LayoutInterceptCallback;

class CustomOneTouchListView : public cocos2d::ui::ListView
{
public:
    virtual ~CustomOneTouchListView();
    CREATE_FUNC(CustomOneTouchListView);
    virtual bool init() override;
    
    virtual void handlePressLogic(cocos2d::Touch *touch) override;
    virtual void handleMoveLogic(cocos2d::Touch *touch) override;
    virtual void handleReleaseLogic(cocos2d::Touch *touch) override;
    
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unusedEvent) override;
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unusedEvent) override;
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unusedEvent) override;
    virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unusedEvent) override;
    
    virtual void interceptTouchEvent(cocos2d::ui::Widget::TouchEventType event,cocos2d::ui::Widget* sender,cocos2d::Touch* touch) override;
    
    bool _canHandleLogic;
};

class CustomOneTouchPageView : public cocos2d::ui::PageView
{
public:
    virtual ~CustomOneTouchPageView();
    CREATE_FUNC(CustomOneTouchPageView);
    virtual bool init();
    
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unusedEvent);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unusedEvent);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unusedEvent);
    virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unusedEvent);
};

class CustomSeparateTouchLayout : public cocos2d::ui::Layout
{
public:
    
    CREATE_FUNC(CustomSeparateTouchLayout);
    CustomSeparateTouchLayout();
    virtual ~CustomSeparateTouchLayout();
    
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unusedEvent);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unusedEvent);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unusedEvent);
    virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unusedEvent);
    
    virtual void interceptTouchEvent(cocos2d::ui::Widget::TouchEventType event, cocos2d::ui::Widget* sender, cocos2d::Touch *touch);
    
    void setLayoutInterceptCallback(const LayoutInterceptCallback& callback) { _callback = callback; }
    
CC_CONSTRUCTOR_ACCESS:
    int _touchID;
    LayoutInterceptCallback _callback;
};


class CustomOneTouchLayout : public cocos2d::ui::Layout
{
public:
    virtual ~CustomOneTouchLayout();
    CustomOneTouchLayout();
    CREATE_FUNC(CustomOneTouchLayout);
    
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unusedEvent);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unusedEvent);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unusedEvent);
    virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unusedEvent);

};

class CustomOneTouchSprite : public CustomOneTouchLayout
{
public:
    static CustomOneTouchSprite* create(cocos2d::SpriteFrame* frame);
    CustomOneTouchSprite();
    virtual bool init(cocos2d::SpriteFrame* frame);
    cocos2d::ui::Scale9Sprite* getSprite();
    void setScale9Enable(const bool& scale9);
    void setCap(const cocos2d::Rect& rect);
    virtual void setContentSize(const cocos2d::Size& contentSize) override;
CC_CONSTRUCTOR_ACCESS:
    cocos2d::ui::Scale9Sprite* _sprite;
};

class CustomOneTouchImageView : public cocos2d::ui::ImageView
{
public:
    CustomOneTouchImageView();
    virtual ~CustomOneTouchImageView();
    static CustomOneTouchImageView* create(const std::string& image);
    CREATE_FUNC(CustomOneTouchImageView);
    
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unusedEvent);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unusedEvent);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unusedEvent);
    virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unusedEvent);
    
    void setAutoReleaseTexture(bool);
    
CC_CONSTRUCTOR_ACCESS:
    bool _autoReleaseTexture;
};

class CustomScale9Sprite : public cocos2d::ui::Scale9Sprite
{
public:
    static CustomScale9Sprite* create(const std::string& file);
};


