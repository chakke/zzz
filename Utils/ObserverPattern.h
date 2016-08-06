//
//  ObserverPattern.h
//  HoverUp
//
//  Created by Manh Tran on 3/11/15.
//
//

#ifndef __HoverUp__ObserverPattern__
#define __HoverUp__ObserverPattern__

class Observable;
class Observer;

#include "cocos2d.h"

struct CallbackData : public cocos2d::Ref
{
    std::function<void(cocos2d::Ref*)> _callback;
};

class Observable
{
public:
    virtual void listen(Observer*, cocos2d::Ref*) = 0;
};

class Observer
{
public:
    virtual ~Observer();
    virtual void addDestination(Observable*, bool strong = true);
    virtual void removeDestination(Observable*);
    virtual void sendData(cocos2d::Ref*, bool release = true);
CC_CONSTRUCTOR_ACCESS:
    std::vector<Observable*> _obs;
    cocos2d::Vector<cocos2d::Ref*> _strongList;
    void tryRemoveStrong(Observable*);
};

#endif /* defined(__HoverUp__ObserverPattern__) */
