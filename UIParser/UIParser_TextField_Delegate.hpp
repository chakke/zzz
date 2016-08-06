//
//  UIParser_TextField_Delegate.hpp
//  Busino
//
//  Created by Manh Tran on 1/19/16.
//
//

#ifndef UIParser_TextField_Delegate_hpp
#define UIParser_TextField_Delegate_hpp

#include "UIParserDelegate.hpp"

class UIParserTextFieldDelegate : public UIParserDelegate
{
public:
    CREATE_UIPARSER_DELEGATE(UIParserTextFieldDelegate);
    virtual cocos2d::Node* createNode(const pugi::xml_node& node);
    virtual void constraintWithParent(const pugi::xml_node& node, const pugi::xml_node& prev_node, cocos2d::Node* parent, cocos2d::Node* recent);
};

#endif /* UIParser_TextField_Delegate_hpp */
