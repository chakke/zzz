//
//  Controller.hpp
//  Busino
//
//  Created by Manh Tran on 1/19/16.
//
//

#ifndef Controller_hpp
#define Controller_hpp

#include "cocos2d.h"
#include "../Utils/ObserverPattern.h"

class Controller : public cocos2d::Ref, public Observer, public Observable
{
public:
    CREATE_FUNC(Controller);
    
    Controller();
    virtual ~Controller();
    
    virtual bool init();
    
    void scheduleUpdate();
    void unscheduleUpdate();
    
    virtual void update(float delta);
    
    virtual void setView(cocos2d::Node* view);
    virtual void addSubController(Controller* controller);
    virtual void removeSubController(Controller* controller, bool recursive);
    virtual void removeSelf(bool recursive);
    virtual void setUserData(cocos2d::Ref* data);
    virtual void listen(Observer* sender, cocos2d::Ref* ref);
    
    virtual void onRemove();
    virtual void onLinked();
    
    cocos2d::Node* getView();
    
    template <typename T>
    inline T getUserData() const { return static_cast<T>(_userData); }
    
    const cocos2d::Vector<Controller*>& getSubControllers() { return _subController; }
    Controller* getParent() { return _parent; }

CC_CONSTRUCTOR_ACCESS:
    cocos2d::Node* _view;
    cocos2d::Vector<Controller*> _subController;
    cocos2d::Ref* _userData;
    Controller* _parent;
    int _id;
};

#endif /* Controller_hpp */
