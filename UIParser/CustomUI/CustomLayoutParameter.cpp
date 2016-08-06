//
//  CustomLayoutParameter.cpp
//  Busino
//
//  Created by Manh Tran on 1/22/16.
//
//

#include "CustomLayoutParameter.hpp"

const UIPadding UIPadding::ZERO(0,0,0,0);

UIPadding::UIPadding()
{
    _top = 0;
    _left = 0;
    _right = 0;
    _bottom = 0;
}

UIPadding::UIPadding(float top, float bottom, float left, float right)
{
    _top = top;
    _left = left;
    _right = right;
    _bottom = bottom;
}

UIPadding::UIPadding(const UIPadding& other)
{
    _top = other._top;
    _left = other._left;
    _right = other._right;
    _bottom = other._bottom;
}

UIPadding& UIPadding::operator= (const UIPadding& other)
{
    _top = other._top;
    _bottom = other._bottom;
    _left = other._left;
    _right = other._right;
    return *this;
}

void UIPadding::setPadding(float left, float top, float right, float bottom)
{
    _top = top;
    _left = left;
    _right = right;
    _bottom = bottom;
}
bool UIPadding::equals(const UIPadding& target) const
{
    return _top == target._top && _left == target._left && _right == target._right && _bottom == target._bottom;
}

//----------------------------------------------------------------------------

CustomLinearLayoutParameter* CustomLinearLayoutParameter::create()
{
    auto ret = new CustomLinearLayoutParameter();
    ret->autorelease();
    return ret;
}
//override functions.
cocos2d::ui::LayoutParameter* CustomLinearLayoutParameter::createCloneInstance()
{
    auto ret = new CustomLinearLayoutParameter();
    ret->copyProperties(this);
    ret->_ui_padding = this->_ui_padding;
    ret->autorelease();
    return ret;
}
void CustomLinearLayoutParameter::copyProperties(LayoutParameter* model)
{
    LinearLayoutParameter::copyProperties(model);
}

//----------------------------------------------------------------------------

CustomRelativeLayoutParameter* CustomRelativeLayoutParameter::create()
{
    auto ret = new CustomRelativeLayoutParameter();
    ret->autorelease();
    return ret;
}
//override functions.
cocos2d::ui::LayoutParameter* CustomRelativeLayoutParameter::createCloneInstance()
{
    auto ret = new CustomRelativeLayoutParameter();
    ret->copyProperties(this);
    ret->_ui_padding = this->_ui_padding;
    ret->autorelease();
    return ret;
}
void CustomRelativeLayoutParameter::copyProperties(LayoutParameter* model)
{
    RelativeLayoutParameter::copyProperties(model);
}