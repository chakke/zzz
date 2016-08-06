//
//  UIParser_ListView_Delegate.cpp
//  Busino
//
//  Created by Manh Tran on 1/16/16.
//
//

#include "UIParser_ListView_Delegate.hpp"
#include "UIConstraint/UIConstraint_Resize.hpp"
#include "CustomUI/CustomUIListView.hpp"

USING_NS_CC;

cocos2d::Node* UIParserListViewDelegate::createNode(const pugi::xml_node& node)
{
    auto view = CustomUIListView::create();
    view->setAnchorPoint(Vec2(0.5, 0.5));
    view->setBounceEnabled(true);
    view->setScrollBarEnabled(false);
    bool has_type = false;
    
    for (auto it = node.attributes_begin(); it != node.attributes_end(); it++)
    {
        if (strcmp(it->name(), "type") == 0)
        {
            has_type = true;
            if (strcmp(it->value(), "vertical") == 0)
            {
                view->setDirection(ui::ScrollView::Direction::VERTICAL);
                sendData(UIConstraint_Resize_ListView_Height::create(view), false);
            }
            else if (strcmp(it->value(), "horizontal") == 0)
            {
                view->setDirection(ui::ScrollView::Direction::HORIZONTAL);
                sendData(UIConstraint_Resize_ListView_Width::create(view), false);
            }
        }
    }
    if (!has_type) // default is vertical
    {
        view->setDirection(ui::ScrollView::Direction::VERTICAL);
        sendData(UIConstraint_Resize_ListView_Height::create(view), false);
    }
    
    return view;
}

void UIParserListViewDelegate::constraintWithParent(const pugi::xml_node& node, const pugi::xml_node& prev_node, cocos2d::Node* parent, cocos2d::Node* recent)
{
    
}