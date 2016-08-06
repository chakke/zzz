//
//  UIParser_PageView_Delegate.cpp
//  GameBai69
//
//  Created by Manh Tran on 3/22/16.
//
//

#include "UIParser_PageView_Delegate.hpp"
#include "UIConstraint/UIConstraint_Resize.hpp"
#include "CustomUI/CustomUIPageView.hpp"

cocos2d::Node* UIParserPageViewDelegate::createNode(const pugi::xml_node& node)
{
    auto view = CustomUIPageView::create();
    view->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
    
    bool has_type = false;
    
    for (auto it = node.attributes_begin(); it != node.attributes_end(); it++)
    {
        if (strcmp(it->name(), "type") == 0)
        {
            has_type = true;
            if (strcmp(it->value(), "vertical") == 0)
            {
                view->setDirection(cocos2d::ui::PageView::Direction::VERTICAL);
            }
            else if (strcmp(it->value(), "horizontal") == 0)
            {
                view->setDirection(cocos2d::ui::PageView::Direction::HORIZONTAL);
            }
        }
    }
    if (!has_type) // default is vertical
    {
        view->setDirection(cocos2d::ui::PageView::Direction::HORIZONTAL);
    }
    return view;
}

void UIParserPageViewDelegate::constraintWithParent(const pugi::xml_node& node, const pugi::xml_node& prev_node, cocos2d::Node* parent, cocos2d::Node* recent)
{
    
}