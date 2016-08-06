//
//  ParserAction.hpp
//  Busino
//
//  Created by Manh Tran on 1/18/16.
//
//

#ifndef ParserAction_hpp
#define ParserAction_hpp

#include "cocos2d.h"

class ParserAction
{
public:
    static ParserAction* getInstance();
    virtual ~ParserAction();
    bool hasAction(const std::string&);
    cocos2d::Action* getAction(const std::string&);
    void setAction(const std::string&, cocos2d::Action*, bool clone = true);
private:
    cocos2d::Map<std::string, cocos2d::Action*> _actions;
};

#endif /* ParserAction_hpp */
