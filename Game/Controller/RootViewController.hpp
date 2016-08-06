
#ifndef RootViewController_hpp
#define RootViewController_hpp
#include "cocos2d.h"
#include "../../AppController/Controller.hpp"

class RootViewController : public Controller
{
public:
    CREATE_FUNC(RootViewController);
    
    virtual bool init();
    
    virtual void onRemove();
    
    virtual void onLinked();
    
    virtual void update(float delta);
    
    virtual void listen(Observer* sender, cocos2d::Ref* ref);
};

#endif /* RootViewController_hpp */
