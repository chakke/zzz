//
//  UIParser_Layout_Delegate.cpp
//  Busino
//
//  Created by Manh Tran on 1/15/16.
//
//

#include "UIParser_Layout_Delegate.hpp"
#include "CustomUI/CustomUILayout.hpp"
#include "Atlas/AtlasCache.hpp"

USING_NS_CC;

cocos2d::Node* UIParserLayoutDelegate::createNode(const pugi::xml_node& node)
{
    auto ret = CustomUILayout::create();
    ret->setAnchorPoint(Vec2(0.5, 0.5));
    
    Rect cap;
    bool scale9 = false;
    
    for (auto it = node.attributes_begin(); it != node.attributes_end(); it++)
    {
        if (strcmp(it->name(), "cap_left") == 0)
        {
            cap.origin.x = atof(it->value());
            scale9 = true;
        }
        else if (strcmp(it->name(), "cap_top") == 0)
        {
            cap.origin.y = atof(it->value());
            scale9 = true;
        }
        else if (strcmp(it->name(), "cap_right") == 0)
        {
            cap.size.width = atof(it->value());
            scale9 = true;
        }
        else if (strcmp(it->name(), "cap_bottom") == 0)
        {
            cap.size.height = atof(it->value());
            scale9 = true;
        }
    }
    
    std::string atlas;
    std::string frame;
    
    for (auto it = node.attributes_begin(); it != node.attributes_end(); it++)
    {
        if (strcmp(it->name(), "type") == 0)
        {
            if (strcmp(it->value(), "vertical") == 0)
            {
                ret->setLayoutType(ui::Layout::Type::VERTICAL);
            }
            else if (strcmp(it->value(), "horizontal") == 0)
            {
                ret->setLayoutType(ui::Layout::Type::HORIZONTAL);
            }
            else if (strcmp(it->value(), "relative") == 0)
            {
                ret->setLayoutType(ui::Layout::Type::RELATIVE);
            }
            else if (strcmp(it->value(), "absolute") == 0)
            {
                ret->setLayoutType(ui::Layout::Type::ABSOLUTE);
            }
        } 
        else if(strcmp(it->name(), "background") == 0)
        {
            ret->setCustomBackground(it->value());
            ret->setCustomBackgroundScale9(scale9);
            ret->setCustomBackgroundCap(cap);
            
//            ret->setBackGroundImage(it->value());
//            if (scale9)
//            {
//                ret->setBackGroundImageScale9Enabled(true);
//                ret->setBackGroundImageCapInsets(cap);
//            }
        }
        else if(strcmp(it->name(), "atlas") == 0)
        {
            atlas = it->value();
        }
        else if(strcmp(it->name(), "frame") == 0)
        {
            frame = it->value();
        }
    }
    
    if (!atlas.empty() && !frame.empty())
    {
//        SpriteFrameCache::getInstance()->addSpriteFrame(atlas_cache::getSpriteFrame(atlas, frame), frame);
        ret->setCustomBackground(atlas_cache::getSpriteFrame(atlas, frame));
        ret->setCustomBackgroundScale9(scale9);
        ret->setCustomBackgroundCap(cap);
//        ret->setBackGroundImage(frame, cocos2d::ui::Widget::TextureResType::PLIST);
//        ret->setBackGroundImageScale9Enabled(true);
//        ret->setBackGroundImageCapInsets(cap);
//        SpriteFrameCache::getInstance()->removeSpriteFrameByName(frame);
    }
    
    return ret;
}

void UIParserLayoutDelegate::constraintWithParent(const pugi::xml_node& node, const pugi::xml_node& prev_node, cocos2d::Node* parent, cocos2d::Node* recent)
{
    
}