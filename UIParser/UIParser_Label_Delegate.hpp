//
//  UIParser_Label_Delegate.hpp
//  Busino
//
//  Created by Manh Tran on 1/15/16.
//
//

#ifndef UIParser_Label_Delegate_hpp
#define UIParser_Label_Delegate_hpp

#include "UIParserDelegate.hpp"

class UIParserLabelDelegate : public UIParserDelegate
{
public:
    CREATE_UIPARSER_DELEGATE(UIParserLabelDelegate);
    virtual cocos2d::Node* createNode(const pugi::xml_node& node);
    virtual void constraintWithParent(const pugi::xml_node& node, const pugi::xml_node& prev_node, cocos2d::Node* parent, cocos2d::Node* recent);
};

#endif /* UIParser_Label_Delegate_hpp */
