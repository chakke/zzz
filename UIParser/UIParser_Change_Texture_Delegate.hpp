//
//  UIParser_Change_Texture_Delegate.hpp
//  GameBai69
//
//  Created by Manh Tran on 2/22/16.
//
//

#ifndef UIParser_Change_Texture_Delegate_hpp
#define UIParser_Change_Texture_Delegate_hpp

#include "UIParserDelegate.hpp"

class UIParserChangeTextureDelegate : public UIParserDelegate
{
public:
    CREATE_UIPARSER_DELEGATE(UIParserChangeTextureDelegate );
    virtual cocos2d::Node* createNode(const pugi::xml_node& node);
    virtual void constraintWithParent(const pugi::xml_node& node, const pugi::xml_node& prev_node, cocos2d::Node* parent, cocos2d::Node* recent);
};

#endif /* UIParser_Change_Texture_Delegate_hpp */
