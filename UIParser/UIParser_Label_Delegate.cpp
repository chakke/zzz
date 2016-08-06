//
//  UIParser_Label_Delegate.cpp
//  Busino
//
//  Created by Manh Tran on 1/15/16.
//
//

#include "UIParser_Label_Delegate.hpp"
#include "CustomUI/CustomUIRichText.h"

USING_NS_CC;

cocos2d::Node* UIParserLabelDelegate::createNode(const pugi::xml_node& node)
{
    auto ret = CustomRichText::create();
    ret->ignoreContentAdaptWithSize(false);
    
    for (auto it = node.attributes_begin(); it != node.attributes_end(); it++)
    {
        if (strcmp(it->name(), "type") == 0)
        {
            if (strcmp(it->value(), "nowrap") == 0)
            {
                ret->setOnLine(true);
            }
        }
    }
    
    return ret;
}

void UIParserLabelDelegate::constraintWithParent(const pugi::xml_node& node, const pugi::xml_node& prev_node, cocos2d::Node* parent, cocos2d::Node* recent)
{

}