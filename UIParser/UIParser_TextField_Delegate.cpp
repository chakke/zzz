//
//  UIParser_TextField_Delegate.cpp
//  Busino
//
//  Created by Manh Tran on 1/19/16.
//
//

#include "UIParser_TextField_Delegate.hpp"
#include "CustomUI/CustomUIEditBox.hpp"
#include "UIParserUtils.hpp"

USING_NS_CC;

cocos2d::Node* UIParserTextFieldDelegate::createNode(const pugi::xml_node& node)
{
    ui::Scale9Sprite* sprite = ui::Scale9Sprite::create(Rect(20,20,20,20), "res/primitive/border_stroke_100x100.png");
    auto ret = CustomUIEditBox::create(Size(1000,100), sprite);
    ret->setReturnType(ui::EditBox::KeyboardReturnType::SEARCH);
    ret->setDelegate(_parser);
    
    for (auto it = node.attributes_begin(); it != node.attributes_end(); it++)
    {
        if (strcmp(it->name(), "fontsize") == 0)
        {
            ret->setFontSize(atoi(it->value()));
            ret->setPlaceholderFontSize(atoi(it->value()));
        }
        else if (strcmp(it->name(), "fontcolor") == 0)
        {
            ret->setFontColor(ui_parser_utils::convertColor(it->value()));
        }
        else if (strcmp(it->name(), "placeholder") == 0)
        {
            ret->setPlaceHolder(it->value());
        }
        else if (strcmp(it->name(), "placeholdercolor") == 0)
        {
            ret->setPlaceholderFontColor(ui_parser_utils::convertColor(it->value()));
        }
        else if (strcmp(it->name(), "inputmode") == 0)
        {
            if (strcmp(it->value(), "decimal") == 0)
            {
                ret->setInputMode(ui::EditBox::InputMode::DECIMAL);
            }
            else if (strcmp(it->value(), "email") == 0)
            {
                ret->setInputMode(ui::EditBox::InputMode::EMAIL_ADDRESS);
            }
            else if (strcmp(it->value(), "numeric") == 0)
            {
                ret->setInputMode(ui::EditBox::InputMode::NUMERIC);
            }
            else if (strcmp(it->value(), "phone") == 0)
            {
                ret->setInputMode(ui::EditBox::InputMode::PHONE_NUMBER);
            }
            else if (strcmp(it->value(), "singleline") == 0)
            {
                ret->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
            }
            else if (strcmp(it->value(), "url") == 0)
            {
                ret->setInputMode(ui::EditBox::InputMode::URL);
            }
        }
        else if(strcmp(it->name(), "inputflag") == 0)
        {
            if (strcmp(it->value(), "sentence") == 0)
            {
                ret->setInputFlag(ui::EditBox::InputFlag::INITIAL_CAPS_SENTENCE);
            }
            else if (strcmp(it->value(), "password") == 0)
            {
                ret->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
            }
        }
    }
    return ret;
}

void UIParserTextFieldDelegate::constraintWithParent(const pugi::xml_node& node, const pugi::xml_node& prev_node, cocos2d::Node* parent, cocos2d::Node* recent)
{
    
}