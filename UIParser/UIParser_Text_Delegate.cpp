//
//  UIParser_Text_Delegate.cpp
//  Busino
//
//  Created by Manh Tran on 1/15/16.
//
//

#include "UIParser_Text_Delegate.hpp"
#include "CustomUI/CustomUIRichText.h"
#include "UIParserUtils.hpp"

USING_NS_CC;

cocos2d::Node* UIParserTextDelegate::createNode(const pugi::xml_node& node)
{
    return nullptr;
}

void UIParserTextDelegate::constraintWithParent(const pugi::xml_node& node, const pugi::xml_node& prev_node, cocos2d::Node* parent, cocos2d::Node* recent)
{
    Color3B color = Color3B::WHITE;
    std::string font = "fonts/SF-UI-Display-Regular.otf";
    int size = 30;
    int opacity = 255;
    for (auto it = prev_node.attributes_begin(); it != prev_node.attributes_end(); it++)
    {
        if (strcmp(it->name(), "color") == 0)
        {
            color = ui_parser_utils::convertColor(it->value());
        }
        else if (strcmp(it->name(), "font") == 0)
        {
            font = it->value();
        }
        else if (strcmp(it->name(), "size") == 0)
        {
            size = atoi(it->value());
        }
        else if (strcmp(it->name(), "opacity") == 0)
        {
            opacity = atoi(it->value());
        }
    }
    
    auto richtext = dynamic_cast<CustomRichText*>(parent);
    if (richtext)
    {
        auto element = CustomRichElementText::create(0, color, opacity, node.value(), font, size);
        richtext->pushBackElement(element);
    }
}