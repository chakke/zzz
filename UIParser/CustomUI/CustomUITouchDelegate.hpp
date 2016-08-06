//
//  CustomUITouchDelegate.hpp
//  Busino
//
//  Created by Manh Tran on 1/18/16.
//
//

#ifndef CustomUITouchDelegate_hpp
#define CustomUITouchDelegate_hpp

#include "cocos2d.h"
#include "ui/UILayout.h"

typedef std::function<void(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)> OnCustomUITouchDelegate;

class CustomUITouchDelegate : public cocos2d::Ref
{
public:
    static CustomUITouchDelegate* create(const std::string& name);
    CustomUITouchDelegate();
    virtual ~CustomUITouchDelegate();
    
    const std::string& getName() { return _name; }
    
    void setName(const std::string& name) { _name = name; }
    
    void setForward(CustomUITouchDelegate* forward);
    CustomUITouchDelegate* getForward() { return _forward; }
    
    void setDelegate(const OnCustomUITouchDelegate& delegate) { _delegate = delegate; }
    const OnCustomUITouchDelegate& getDelegate() { return _delegate; }
    
private:
    std::string _name;
    CustomUITouchDelegate* _forward;
    OnCustomUITouchDelegate _delegate;
};

class CustomUITouchDelegateComponent : public cocos2d::Component
{
public:
    static CustomUITouchDelegateComponent* create(const std::string& name);
    virtual ~CustomUITouchDelegateComponent();
    
    cocos2d::Map<std::string, CustomUITouchDelegate*> _delegates;
};

#endif /* CustomUITouchDelegate_hpp */
