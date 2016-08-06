//
//  UIParser_Button_Delegate.cpp
//  Busino
//
//  Created by Manh Tran on 1/16/16.
//
//

#include "UIParser_Button_Delegate.hpp"
#include "ui/UILayout.h"
#include "UIParser.hpp"

USING_NS_CC;

cocos2d::Node* UIParserButtonDelegate::createNode(const pugi::xml_node& node)
{
    cocos2d::Node* ret = nullptr;
    
    for (auto it = node.attributes_begin(); it != node.attributes_end(); it++)
    {
        if (strcmp(it->name(), "style") == 0)
        {
            ret = UIParser::parse(it->value());
        }
    }
    
    return ret;
}

void UIParserButtonDelegate::constraintWithParent(const pugi::xml_node& node, const pugi::xml_node& prev_node, cocos2d::Node* parent, cocos2d::Node* recent)
{
    
}