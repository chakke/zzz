//
//  UIParser_Change_Texture_Delegate.cpp
//  GameBai69
//
//  Created by Manh Tran on 2/22/16.
//
//

#include "UIParser_Change_Texture_Delegate.hpp"
#include "UIParserUtils.hpp"
#include "CustomUI/CustomUIImageView.hpp"
#include "Atlas/AtlasCache.hpp"

cocos2d::Node* UIParserChangeTextureDelegate::createNode(const pugi::xml_node& node)
{
    return nullptr;
}

void UIParserChangeTextureDelegate::constraintWithParent(const pugi::xml_node& node, const pugi::xml_node& prev_node, cocos2d::Node* parent, cocos2d::Node* recent)
{
    if (parent)
    {
        std::string src;
        std::string atlas;
        std::string frame;
        cocos2d::Node* target = nullptr;
        
        for (auto it = node.attributes_begin(); it != node.attributes_end(); it++)
        {
            if (strcmp(it->name(), "src") == 0)
            {
                src = it->value();
            }
            else if (strcmp(it->name(), "atlas") == 0)
            {
                atlas = it->value();
            }
            else if (strcmp(it->name(), "frame") == 0)
            {
                frame = it->value();
            }
            else if (strcmp(it->name(), "target") == 0)
            {
                std::vector<std::string> ids;
                ui_parser_utils::split(it->value(), ':', ids);
                
                target = parent;
                for (int i = 0; i < ids.size(); i++)
                {
                    if (ids[i].compare("this") != 0 && target)
                    {
                        target = target->getChildByName(ids[i]);
                    }
                }
            }
        }
        
        auto imageview = dynamic_cast<CustomUIImageView*>(target);
        if (imageview)
        {
            if (!src.empty())
            {
                imageview->loadTexture(src);
            }
            else if(!atlas.empty() && !frame.empty())
            {
                imageview->setSpriteFrame(atlas_cache::getSpriteFrame(atlas, frame));
            }
        }
    }
}