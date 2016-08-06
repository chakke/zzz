//
//  UIConstraintManager.cpp
//  Busino
//
//  Created by Manh Tran on 1/16/16.
//
//

#include "UIConstraintManager.hpp"

USING_NS_CC;

UIConstraintManager* UIConstraintManager::create(const std::string& name)
{
    auto ret = new UIConstraintManager();
    ret->init();
    ret->setName(name);
    ret->autorelease();
    return ret;
}

UIConstraintManager::UIConstraintManager()
{
    
}

UIConstraintManager::~UIConstraintManager()
{
    _constraints.clear();
}

bool UIConstraintManager::init()
{
    if( ! Component::init())
        return false;
    
    return true;
}

void UIConstraintManager::pushConstraint(UIConstraint* constraint)
{
    _constraints.pushBack(constraint);
}

void UIConstraintManager::custom_update(float delta)
{
    for (int i = 0; i < _constraints.size(); i++)
    {
        auto constraint = _constraints.at(i);
		if (constraint) {
			if (constraint->getTarget() && !constraint->getTarget()->getScene())
			{
				_constraints.erase(i);
				i--;
			}
			else constraint->update(delta);
		}
    }
}

void UIConstraintManager::update(float delta)
{
    
}