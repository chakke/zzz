//
//  CustomUILayout.cpp
//  Busino
//
//  Created by Manh Tran on 1/18/16.
//
//

#include "CustomUILayout.hpp"
#include "CustomLayoutParameter.hpp"
#include "ui/UIScale9Sprite.h"

USING_NS_CC;

CustomUILayout::CustomUILayout() : _onTouchDelegate(nullptr), _need_swallow(true), _custom_background(nullptr)
{
    
}

CustomUILayout::~CustomUILayout()
{
    _down_delegates.clear();
    _move_delegates.clear();
    _end_delegates.clear();
    _cancel_delegates.clear();
}

bool CustomUILayout::init()
{
    if (!Layout::init())
    {
        return false;
    }
    
    addTouchEventListener(CC_CALLBACK_2(CustomUILayout::onTouch, this));
    return true;
}

void CustomUILayout::setContentSize(const Size& contentSize)
{
    Layout::setContentSize(contentSize);
    if (_custom_background) {
        _custom_background->setContentSize(getContentSize());
    }
//    auto scale9Image = dynamic_cast<cocos2d::ui::Scale9Sprite*>(_backGroundImage);
//    if (scale9Image && !scale9Image->isScale9Enabled())
//    {
//        scale9Image->setPreferredSize(getContentSize());
//        scale9Image->setContentSize(getContentSize());
//        CCLOG("on size change %f, %f", getContentSize().width, getContentSize().height);
//    }
}

void CustomUILayout::onSizeChanged()
{
    Layout::onSizeChanged();
    if (_custom_background) {
        _custom_background->setContentSize(getContentSize());
    }
//    auto scale9Image = dynamic_cast<cocos2d::ui::Scale9Sprite*>(_backGroundImage);
//    if (scale9Image && !scale9Image->isScale9Enabled())
//    {
//        scale9Image->setPreferredSize(getContentSize());
//        scale9Image->setContentSize(getContentSize());
//        CCLOG("on size change %f, %f", getContentSize().width, getContentSize().height);
//    }
}

void CustomUILayout::requireBackground()
{
    if (!_custom_background) {
        _custom_background = CustomUIImageView::create();
        addProtectedChild(_custom_background, -1, -1);
        _custom_background->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
        _custom_background->setNormalizedPosition(cocos2d::Vec2(0.5, 0.5));
        _custom_background->ignoreContentAdaptWithSize(false);
    }
}

void CustomUILayout::setCustomBackground(const std::string& image)
{
    requireBackground();
    _custom_background->loadTexture(image);
}

void CustomUILayout::setCustomBackground(cocos2d::SpriteFrame* frame)
{
    requireBackground();
    _custom_background->setSpriteFrame(frame);
}

void CustomUILayout::setCustomBackgroundScale9(const bool& scale9)
{
    requireBackground();
    _custom_background->setScale9Enabled(scale9);
}

void CustomUILayout::setCustomBackgroundCap(const cocos2d::Rect& cap)
{
    requireBackground();
    _custom_background->setCapInsets(cap);
}

void CustomUILayout::setNeedSwallow(bool need)
{
    _need_swallow = need;
    setSwallowTouches(_need_swallow);
}

void CustomUILayout::setTouchEnabled(bool enabled)
{
    Layout::setTouchEnabled(enabled);
    setSwallowTouches(_need_swallow);
}

void CustomUILayout::setOnTouchDelegate(CustomUITouchDelegate* delegate)
{
    CC_SAFE_RELEASE_NULL(_onTouchDelegate);
    _onTouchDelegate = delegate;
    CC_SAFE_RETAIN(_onTouchDelegate);
}

void CustomUILayout::onTouch(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
    switch (type)
    {
        case cocos2d::ui::Widget::TouchEventType::BEGAN:
            for (auto it = _down_delegates.begin(); it != _down_delegates.end(); it++)
            {
                (*it)(this);
            }
            break;
        case cocos2d::ui::Widget::TouchEventType::MOVED:
            for (auto it = _move_delegates.begin(); it != _move_delegates.end(); it++)
            {
                (*it)(this);
            }
            break;
        case cocos2d::ui::Widget::TouchEventType::ENDED:
            for (auto it = _end_delegates.begin(); it != _end_delegates.end(); it++)
            {
                (*it)(this);
            }
            break;
        case cocos2d::ui::Widget::TouchEventType::CANCELED:
            for (auto it = _cancel_delegates.begin(); it != _cancel_delegates.end(); it++)
            {
                (*it)(this);
            }
            break;
        default:
            break;
    }
    CustomUITouchDelegate* delegate = _onTouchDelegate;
    
    while (delegate)
    {
        if (delegate->getDelegate())
        {
            delegate->getDelegate()(sender, type);
        }
        delegate = delegate->getForward();
    }
}

void CustomUILayout::addChild(Node* child)
{
    addChild(child, child->getLocalZOrder(), child->getTag());
}

void CustomUILayout::addChild(Node * child, int localZOrder)
{
    addChild(child, localZOrder, child->getTag());
}

void CustomUILayout::addChild(Node *child, int zOrder, int tag)
{
    if (dynamic_cast<Widget*>(child)) {
        customSupplyTheLayoutParameterLackToChild(static_cast<Widget*>(child));
    }
    Widget::addChild(child, zOrder, tag);
    _doLayoutDirty = true;
}

void CustomUILayout::addChild(Node* child, int zOrder, const std::string &name)
{
    if (dynamic_cast<Widget*>(child)) {
        customSupplyTheLayoutParameterLackToChild(static_cast<Widget*>(child));
    }
    Widget::addChild(child, zOrder, name);
    _doLayoutDirty = true;
}

void CustomUILayout::attach_node(cocos2d::Node* node)
{
    addChild(node);
}

void CustomUILayout::customSupplyTheLayoutParameterLackToChild(Widget *child)
{
    if (!child)
    {
        return;
    }
    cocos2d::ui::LayoutParameter* param = child->getLayoutParameter();
    CustomLayoutParamaterPadding* padding = dynamic_cast<CustomLayoutParamaterPadding*>(param);
    
    switch (_layoutType)
    {
        case Type::ABSOLUTE:
            break;
        case Type::HORIZONTAL:
        case Type::VERTICAL:
        {
            CustomLinearLayoutParameter* layoutParameter = dynamic_cast<CustomLinearLayoutParameter*>(child->getLayoutParameter());
            if (!layoutParameter)
            {
                auto newparam = CustomLinearLayoutParameter::create();
                if(param)
                {
                    newparam->setMargin(param->getMargin());
                    if (padding) {
                        newparam->_ui_padding = padding->_ui_padding;
                    }
                }
                child->setLayoutParameter(newparam);
            }
            break;
        }
        case Type::RELATIVE:
        {
            CustomRelativeLayoutParameter* layoutParameter = dynamic_cast<CustomRelativeLayoutParameter*>(child->getLayoutParameter());
            if (!layoutParameter)
            {
                auto newparam = CustomRelativeLayoutParameter::create();
                if(param)
                {
                    newparam->setMargin(param->getMargin());
                    if (padding) {
                        newparam->_ui_padding = padding->_ui_padding;
                    }
                }
                child->setLayoutParameter(newparam);
            }
            break;
        }
        default:
            break;
    }
}