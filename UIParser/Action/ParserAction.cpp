//
//  ParserAction.cpp
//  Busino
//
//  Created by Manh Tran on 1/18/16.
//
//

#include "ParserAction.hpp"

USING_NS_CC;

static ParserAction* _instance = nullptr;

ParserAction* ParserAction::getInstance()
{
    if (!_instance)
    {
        _instance = new ParserAction();
    }
    return _instance;
}

ParserAction::~ParserAction()
{
    _actions.clear();
}

bool ParserAction::hasAction(const std::string& key)
{
    return _actions.at(key);
}

cocos2d::Action* ParserAction::getAction(const std::string& key)
{
    auto action = _actions.at(key);
    return action ? action->clone() : nullptr;
}

void ParserAction::setAction(const std::string& key, cocos2d::Action* action, bool clone /* = true */)
{
    _actions.insert(key, clone ? action->clone() : action);
}