//
//  UIConstraint.cpp
//  Busino
//
//  Created by Manh Tran on 1/16/16.
//
//

#include "UIConstraint.hpp"

UIConstraint::UIConstraint() : _target(nullptr)
{
    
}

UIConstraint::~UIConstraint()
{
    CC_SAFE_RELEASE_NULL(_target);
}