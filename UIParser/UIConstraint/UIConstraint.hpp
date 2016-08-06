//
//  UIConstraint.hpp
//  Busino
//
//  Created by Manh Tran on 1/16/16.
//
//

#ifndef UIConstraint_hpp
#define UIConstraint_hpp

#include "cocos2d.h"

class UIConstraint : public cocos2d::Ref
{
public:
    UIConstraint();
    virtual ~UIConstraint();
    virtual void update(float delta) = 0;
    cocos2d::Node* getTarget() { return _target; }
protected:
    cocos2d::Node* _target;
};

#define CREATE_UI_CONSTRAINT(__TYPE__)\
static __TYPE__* create(cocos2d::Node* target) \
{ \
    __TYPE__ *pRet = new(std::nothrow) __TYPE__(); \
    pRet->_target = target;\
    CC_SAFE_RETAIN(target);\
    pRet->autorelease(); \
    return pRet; \
}

#endif /* UIConstraint_hpp */
