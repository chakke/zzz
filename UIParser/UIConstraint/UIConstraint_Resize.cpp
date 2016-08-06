//
//  UIConstraint_Resize.cpp
//  Busino
//
//  Created by Manh Tran on 1/16/16.
//
//

#include "UIConstraint_Resize.hpp"
#include "../CustomUI/CustomUIRichText.h"
#include "../CustomUI/CustomLayoutParameter.hpp"
#include "ui/UILayout.h"
#include "ui/UIImageView.h"
#include "ui/UIListView.h"

USING_NS_CC;

void UIConstraint_Resize_Match_Parent_Width::update(float delta)
{
    auto parent = _target->getParent();
    auto layout_parent = dynamic_cast<ui::Layout*>(parent);
    auto listview_parent = dynamic_cast<ui::ListView*>(parent);
    if (parent)
    {
        float parent_width = parent->getContentSize().width;
        float target_width = _target->getContentSize().width;
        
        auto widget_target = dynamic_cast<ui::Widget*>(_target);
        if (widget_target && widget_target->getLayoutParameter())
        {
            auto param = widget_target->getLayoutParameter();
            auto customparam = dynamic_cast<CustomLayoutParamaterPadding*>(param);
            if (customparam)
            {
                parent_width -= customparam->_ui_padding._left;
                parent_width -= customparam->_ui_padding._right;
            }
        }
        
        if (target_width != parent_width && parent_width > 0)
        {
            auto widget = dynamic_cast<CustomRichText*>(_target);
            if(widget)
            {
                if (fabsf(widget->getLastUpdateWidth() - parent_width) > 0.0016 && parent_width > 0)
                {
                    
                    _target->setContentSize(Size(parent_width, _target->getContentSize().height));
                    widget->updateText();
                }
            }
            else
            {
                
                _target->setContentSize(Size(parent_width, _target->getContentSize().height));
            }
            if (layout_parent) layout_parent->requestDoLayout();
            if (listview_parent) listview_parent->requestDoLayout();
        }
    }
}

void UIConstraint_Resize_Match_Parent_Height::update(float delta)
{
    auto parent = _target->getParent();
    auto layout_parent = dynamic_cast<ui::Layout*>(parent);
    auto listview_parent = dynamic_cast<ui::ListView*>(parent);
    if (parent)
    {
        float parent_height = parent->getContentSize().height;
        float target_height = _target->getContentSize().height;
        auto widget_target = dynamic_cast<ui::Widget*>(_target);
        if (widget_target && widget_target->getLayoutParameter())
        {
            auto param = widget_target->getLayoutParameter();
            auto customparam = dynamic_cast<CustomLayoutParamaterPadding*>(param);
            if (customparam)
            {
                parent_height -= customparam->_ui_padding._top;
                parent_height -= customparam->_ui_padding._bottom;
            }
        }
        if (fabsf(target_height - parent_height) > 0.0016 && parent_height > 0)
        {
            
            _target->setContentSize(Size(_target->getContentSize().width, parent_height));
            if (layout_parent) layout_parent->requestDoLayout();
            if (listview_parent) listview_parent->requestDoLayout();
        }
    }
}

void UIConstraint_Resize_Wrap_Content_Width::update(float delta)
{
    auto parent = _target->getParent();
    auto layout_parent = dynamic_cast<ui::Layout*>(parent);
    auto listview_parent = dynamic_cast<ui::ListView*>(parent);
    
    auto widget_target = dynamic_cast<ui::ImageView*>(_target);
    if (widget_target)
    {
        float ratio = widget_target->getVirtualRendererSize().width / widget_target->getVirtualRendererSize().height;
        float c_ratio = widget_target->getContentSize().width / widget_target->getContentSize().height;
        if (fabsf(ratio - c_ratio) > 0.0016)
        {
          
            widget_target->setContentSize(Size(widget_target->getContentSize().width * ratio / c_ratio, widget_target->getContentSize().height));
            if (layout_parent) layout_parent->requestDoLayout();
            if (listview_parent) listview_parent->requestDoLayout();
        }
        return;
    }
    auto listview_target = dynamic_cast<ui::ListView*>(_target);
    if (listview_target)
    {
        
        return;
    }
    
    auto layout_target = dynamic_cast<ui::Layout*>(_target);
    if (layout_target && layout_target->getLayoutType() == ui::Layout::Type::HORIZONTAL)
    {
        long count = layout_target->getChildrenCount();
        float ch = layout_target->getContentSize().width;
        float rh = 0;
        for (int i = 0; i < count; i++)
        {
            auto node = dynamic_cast<ui::Widget*>(layout_target->getChildren().at(i));
            if(node)
            {
                rh += node->getContentSize().width;
                auto param = node->getLayoutParameter();
                if (param)
                {
                    rh += param->getMargin().left + param->getMargin().right;
                }
            }
        }
        if (fabsf(ch - rh) > 0.0016)
        {
          
            layout_target->setContentSize(Size(rh, layout_target->getContentSize().height));
            layout_target->requestDoLayout();
            if (layout_parent) layout_parent->requestDoLayout();
            if (listview_parent) listview_parent->requestDoLayout();
        }
    }
    else if (layout_target && layout_target->getLayoutType() == ui::Layout::Type::VERTICAL)
    {
        long count = layout_target->getChildrenCount();
        float ch = layout_target->getContentSize().width;
        float rh = 0;
        for (int i = 0; i < count; i++)
        {
            auto node = dynamic_cast<ui::Widget*>(layout_target->getChildren().at(i));
            if(node)
            {
                rh = MAX(rh, node->getContentSize().width);
            }
        }
        if (fabsf(ch - rh) > 0.0016)
        {
          
            layout_target->setContentSize(Size(rh, layout_target->getContentSize().height));
            layout_target->requestDoLayout();
            if (layout_parent) layout_parent->requestDoLayout();
            if (listview_parent) listview_parent->requestDoLayout();
        }
    }
    else if(layout_target && layout_target->getLayoutType() == ui::Layout::Type::ABSOLUTE)
    {
        if (layout_target->getChildrenCount() >= 1)
        {
            auto first = layout_target->getChildren().at(0);
            if(layout_target->getContentSize().width != first->getContentSize().width)
            {
                layout_target->setContentSize(Size(first->getContentSize().width, layout_target->getContentSize().height));
                first->setPositionX(first->getAnchorPoint().x * first->getContentSize().width);
                layout_target->requestDoLayout();
                if (layout_parent) layout_parent->requestDoLayout();
                if (listview_parent) listview_parent->requestDoLayout();
            }
        }
    }
}

void UIConstraint_Resize_Wrap_Content_Height::update(float delta)
{
    auto parent = _target->getParent();
    auto layout_parent = dynamic_cast<ui::Layout*>(parent);
    auto listview_parent = dynamic_cast<ui::ListView*>(parent);
    
    auto widget_target = dynamic_cast<ui::ImageView*>(_target);
    if (widget_target)
    {
        float ratio = widget_target->getVirtualRendererSize().height / widget_target->getVirtualRendererSize().width;
        float c_ratio = widget_target->getContentSize().height / widget_target->getContentSize().width;
        if (fabsf(ratio - c_ratio) > 0.0016)
        {
          
            widget_target->setContentSize(Size(widget_target->getContentSize().width, widget_target->getContentSize().height * ratio / c_ratio));
            if (layout_parent) layout_parent->requestDoLayout();
            if (listview_parent) listview_parent->requestDoLayout();
        }
        return;
    }
    
    auto listview_target = dynamic_cast<ui::ListView*>(_target);
    if (listview_target)
    {
        
        return;
    }
    
    auto layout_target = dynamic_cast<ui::Layout*>(_target);
    if (layout_target && layout_target->getLayoutType() == ui::Layout::Type::VERTICAL)
    {
        long count = layout_target->getChildrenCount();
        float ch = layout_target->getContentSize().height;
        float rh = 0;
        for (int i = 0; i < count; i++)
        {
            auto node = dynamic_cast<ui::Widget*>(layout_target->getChildren().at(i));
            if(node)
            {
                rh += node->getContentSize().height;
                auto param = node->getLayoutParameter();
                if (param)
                {
                    rh += param->getMargin().top + param->getMargin().bottom;
                }
            }
        }
        if (fabsf(ch - rh) > 0.0016)
        {
          
            layout_target->setContentSize(Size(layout_target->getContentSize().width, rh));
            layout_target->requestDoLayout();
            if (layout_parent) layout_parent->requestDoLayout();
            if (listview_parent) listview_parent->requestDoLayout();
        }
    }
    else if (layout_target && layout_target->getLayoutType() == ui::Layout::Type::HORIZONTAL)
    {
        long count = layout_target->getChildrenCount();
        float ch = layout_target->getContentSize().height;
        float rh = 0;
        for (int i = 0; i < count; i++)
        {
            auto node = dynamic_cast<ui::Widget*>(layout_target->getChildren().at(i));
            if(node)
            {
                rh = MAX(rh, node->getContentSize().height);
            }
        }
        if (fabsf(ch - rh) > 0.0016)
        {
          
            layout_target->setContentSize(Size(layout_target->getContentSize().width, rh));
            layout_target->requestDoLayout();
            if (layout_parent) layout_parent->requestDoLayout();
            if (listview_parent) listview_parent->requestDoLayout();
        }
    }
    else if(layout_target && layout_target->getLayoutType() == ui::Layout::Type::ABSOLUTE)
    {
        if (layout_target->getChildrenCount() >= 1)
        {
            auto first = layout_target->getChildren().at(0);
            if(layout_target->getContentSize().height != first->getContentSize().height)
            {
                layout_target->setContentSize(Size(layout_target->getContentSize().width, first->getContentSize().height));
                first->setPositionY(first->getAnchorPoint().y * first->getContentSize().height);
                layout_target->requestDoLayout();
                if (layout_parent) layout_parent->requestDoLayout();
                if (listview_parent) listview_parent->requestDoLayout();
            }
        }
    }
}

void UIConstraint_Resize_ListView_Height::update(float delta)
{
    auto listview = dynamic_cast<ui::ListView*>(_target);
    float lh = listview->getContentSize().height;
    float ch = listview->getInnerContainerSize().height;
    float rh = 0;
    for (int i = 0; i < listview->getChildrenCount(); i++)
    {
        rh += listview->getChildren().at(i)->getContentSize().height;
        rh += listview->getItemsMargin();
    }
    
    if ((fabsf(lh - ch) > 0.0016 && fabsf(ch - rh) > 0.0016 && rh > 0) || (rh > ch))
    {
        listview->setInnerContainerSize(Size(listview->getInnerContainerSize().width, rh));
        listview->requestDoLayout();
       
    }
}

void UIConstraint_Resize_ListView_Width::update(float delta)
{
    auto listview = dynamic_cast<ui::ListView*>(_target);
    float lh = listview->getContentSize().width;
    float ch = listview->getInnerContainerSize().width;
    float rh = 0;
    for (int i = 0; i < listview->getChildrenCount(); i++)
    {
        rh += listview->getChildren().at(i)->getContentSize().width;
        rh += listview->getItemsMargin();
    }
    
    if ((fabsf(lh - ch) > 0.0016 && fabsf(ch - rh) > 0.0016 && rh > 0) || (rh > ch))
    {
        listview->setInnerContainerSize(Size(rh, listview->getInnerContainerSize().height));
        listview->requestDoLayout();
       
    }
}