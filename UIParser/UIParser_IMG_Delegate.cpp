//
//  UIParser_IMG_Delegate.cpp
//  1502
//
//  Created by Manh Tran on 1/15/16.
//
//

#include "UIParser_IMG_Delegate.hpp"
#include "CustomUI/CustomUIImageView.hpp"
#include "Atlas/AtlasCache.hpp"

USING_NS_CC;

cocos2d::Node* UIParserImgDelegate::createNode(const pugi::xml_node& node)
{
    auto ret = CustomUIImageView::create();
    
    std::string atlas;
    std::string frame;
    
    Rect cap;
    bool scale9 = false;
    
    for (auto it = node.attributes_begin(); it != node.attributes_end(); it++)
    {
        if (strcmp(it->name(), "src") == 0)
        {
            ret->loadTexture(it->value());
        }
        else if(strcmp(it->name(), "atlas") == 0)
        {
            atlas = it->value();
        }
        else if(strcmp(it->name(), "frame") == 0)
        {
            frame = it->value();
        }
        else if(strcmp(it->name(), "cap_left") == 0)
        {
            cap.origin.x = atof(it->value());
            scale9 = true;
        }
        else if(strcmp(it->name(), "cap_top") == 0)
        {
            cap.origin.y = atof(it->value());
            scale9 = true;
        }
        else if(strcmp(it->name(), "cap_right") == 0)
        {
            cap.size.width = atof(it->value());
            scale9 = true;
        }
        else if(strcmp(it->name(), "cap_bottom") == 0)
        {
            cap.size.height = atof(it->value());
            scale9 = true;
        }
    }
    
    if (!atlas.empty() && !frame.empty())
    {
        cocos2d::SpriteFrame* spriteFrame = atlas_cache::getSpriteFrame(atlas, frame);
        
        ret->setSpriteFrame(spriteFrame);
    }
    
    ret->ignoreContentAdaptWithSize(false);
    if (scale9) {
        ret->setScale9Enabled(true);
        ret->setCapInsets(cap);
    }
    return ret;
}

void UIParserImgDelegate::constraintWithParent(const pugi::xml_node& node,const pugi::xml_node& prev_node,  cocos2d::Node* parent, cocos2d::Node* recent)
{
    
}