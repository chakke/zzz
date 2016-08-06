//
//  UIParser_Action_Delegate.hpp
//  Busino
//
//  Created by Manh Tran on 1/18/16.
//
//

#ifndef UIParser_Action_Delegate_hpp
#define UIParser_Action_Delegate_hpp

#include "UIParserDelegate.hpp"

class UIParserActionData : public cocos2d::Ref
{
public:
    UIParserActionData()
    {
        autorelease();
    }
    
    virtual cocos2d::FiniteTimeAction* parse() = 0;
};

class UIParserActionDelegate : public UIParserDelegate, public pugi::xml_tree_walker
{
public:
    CREATE_UIPARSER_DELEGATE(UIParserActionDelegate);
    virtual cocos2d::Node* createNode(const pugi::xml_node& node);
    virtual void constraintWithParent(const pugi::xml_node& node, const pugi::xml_node& prev_node, cocos2d::Node* parent, cocos2d::Node* recent);
    
    // Callback that is called when traversal begins
    virtual bool begin(pugi::xml_node& node);
    
    // Callback that is called for each node traversed
    virtual bool for_each(pugi::xml_node& node);
    
    virtual bool end_each(pugi::xml_node& node);
    
    // Callback that is called when traversal ends
    virtual bool end(pugi::xml_node& node);
    
    cocos2d::Vector<UIParserActionData*> _datas;
    cocos2d::Vector<UIParserActionData*> _stacks;
    bool _just_parse;
};

#endif /* UIParser_Action_Delegate_hpp */
