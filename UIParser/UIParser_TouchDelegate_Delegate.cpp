//
//  UIParser_TouchDelegate_Delegate.cpp
//  Busino
//
//  Created by Manh Tran on 1/18/16.
//
//

#include "UIParser_TouchDelegate_Delegate.hpp"

USING_NS_CC;

cocos2d::Node* UIParserTouchDelegateDelegate::createNode(const pugi::xml_node& node)
{
    std::string name = node.attribute("name").value();
    if ( ! _parser->getTouchDelegates()->at(name))
    {
        _parser->getTouchDelegates()->insert(name, CustomUITouchDelegate::create(name));   
    }
    return nullptr;
}

void UIParserTouchDelegateDelegate::constraintWithParent(const pugi::xml_node& node, const pugi::xml_node& prev_node, cocos2d::Node* parent, cocos2d::Node* recent)
{
    
}