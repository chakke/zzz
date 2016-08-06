//
//  CustomUIEditBox.cpp
//  Busino
//
//  Created by Manh Tran on 1/19/16.
//
//

#include "CustomUIEditBox.hpp"

USING_NS_CC;

CustomUIEditBox* CustomUIEditBox::create(const cocos2d::Size& size, const std::string& scale9Image)
{
    auto ret = new CustomUIEditBox();
    ret->initWithSizeAndBackgroundSprite(size, scale9Image);
    ret->autorelease();
    ret->_backgroundSprite->setVisible(false);
    return ret;
}

CustomUIEditBox* CustomUIEditBox::create(const cocos2d::Size& size, ui::Scale9Sprite* sprite)
{
    auto ret = new CustomUIEditBox();
    ret->initWithSizeAndBackgroundSprite(size, sprite);
    ret->autorelease();
    ret->_backgroundSprite->setVisible(false);
    return ret;
}

void CustomUIEditBox::setContentSize(const cocos2d::Size& size)
{
    EditBox::setContentSize(size);
    setFont(_fontName.c_str(), _fontSize);
}

std::string CustomUIEditBox::getString()
{
    return _text;
}

void CustomUIEditBox::attach_node(cocos2d::Node* node)
{
    addChild(node);
}