//
//  UIParserDelegate.hpp
//  1502
//
//  Created by Manh Tran on 1/15/16.
//
//

#ifndef UIParserDelegate_hpp
#define UIParserDelegate_hpp

#include "cocos2d.h"
#include "../Utils/pugixml.hpp"
#include "../Utils/ObserverPattern.h"
#include "UIConstraint/UIConstraint.hpp"
#include "UIParser.hpp"

class UIParser;

class UIParserDelegate : public cocos2d::Ref, public Observer
{
public:
    virtual ~UIParserDelegate()
    {
    }
    virtual cocos2d::Node* createNode(const pugi::xml_node& node) = 0;
    virtual void constraintWithParent(const pugi::xml_node& node, const pugi::xml_node& prev_node, cocos2d::Node* parent, cocos2d::Node* recent) = 0;
    virtual void processCommonConstraint(const pugi::xml_node& node, cocos2d::Node* recent);
    
    UIParser* _parser;
};

#define CREATE_UIPARSER_DELEGATE(__TYPE__)\
static __TYPE__* create(UIParser* parser) \
{ \
    __TYPE__ *pRet = new(std::nothrow) __TYPE__(); \
    pRet->_parser = parser;\
    pRet->addDestination(parser,false);\
    pRet->autorelease(); \
    return pRet; \
}


#endif /* UIParserDelegate_hpp */
