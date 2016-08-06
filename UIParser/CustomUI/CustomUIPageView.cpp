//
//  CustomUIPageView.cpp
//  GameBai69
//
//  Created by Manh Tran on 3/22/16.
//
//

#include "CustomUIPageView.hpp"

void CustomUIPageView::attach_node(cocos2d::Node* node)
{
    auto layout = dynamic_cast<cocos2d::ui::Layout*>(node);
    if (layout)
    {
        addPage(layout);
    }
    else addChild(node);
}