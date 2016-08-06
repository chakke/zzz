//
//  UIConstraintManager.hpp
//  Busino
//
//  Created by Manh Tran on 1/16/16.
//
//

#ifndef UIConstraintManager_hpp
#define UIConstraintManager_hpp

#include "UIConstraint.hpp"

class UIConstraintManager : public cocos2d::Component
{
public:
    static UIConstraintManager* create(const std::string& name);
    UIConstraintManager();
    virtual ~UIConstraintManager();
    virtual bool init();
    virtual void update(float delta);
    
    virtual void custom_update(float delta);
    
    void pushConstraint(UIConstraint* constraint);
    
private:
    cocos2d::Vector<UIConstraint*> _constraints;
};

#endif /* UIConstraintManager_hpp */
