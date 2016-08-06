//
//  CustomUITouchDelegate.cpp
//  Busino
//
//  Created by Manh Tran on 1/18/16.
//
//

#include "CustomUITouchDelegate.hpp"

USING_NS_CC;

CustomUITouchDelegate* CustomUITouchDelegate::create(const std::string& name)
{
    auto ret = new CustomUITouchDelegate();
    ret->setName(name);
    ret->autorelease();
    return ret;
}

CustomUITouchDelegate::CustomUITouchDelegate() : _forward(nullptr), _delegate(nullptr)
{
    
}

CustomUITouchDelegate::~CustomUITouchDelegate()
{
    CC_SAFE_RELEASE_NULL(_forward);
}

void CustomUITouchDelegate::setForward(CustomUITouchDelegate* forward)
{
    CC_SAFE_RELEASE_NULL(_forward);
    _forward = forward;
    CC_SAFE_RETAIN(_forward);
}

//--------------------------------------
CustomUITouchDelegateComponent* CustomUITouchDelegateComponent::create(const std::string& name)
{
    auto ret = new CustomUITouchDelegateComponent();
    ret->init();
    ret->setName(name);
    ret->autorelease();
    return ret;
}

CustomUITouchDelegateComponent::~CustomUITouchDelegateComponent()
{
    _delegates.clear();
}