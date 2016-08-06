#pragma once
#include "../../AppController/Controller.hpp"
#include "../../Data/ConnectionData.hpp"

class PingController : public Controller
{
public:
    CREATE_FUNC(PingController);
    
    virtual bool init();
    
    virtual void onRemove();
    
    virtual void onLinked();
    
    virtual void update(float delta);

private :

	float mTimePing;
};
