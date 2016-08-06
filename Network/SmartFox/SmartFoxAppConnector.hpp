
#ifndef SmartFoxAppConnector_hpp
#define SmartFoxAppConnector_hpp

#include "../AppConnector.hpp"

class SmartFoxAppConnector : public AppConnector
{
public:
    CREATE_FUNC(SmartFoxAppConnector);
    SmartFoxAppConnector();
    virtual ~SmartFoxAppConnector();
    
    virtual bool init();
    
    virtual void update(float delta);
    
    virtual void listen(Observer*, cocos2d::Ref*);
    
    virtual void updateServerConfig();
    
    virtual bool isUdp();
    
    virtual void sendData(cocos2d::Ref*, bool release = true);
    
CC_CONSTRUCTOR_ACCESS:
    void* _connector;
    float _timeout;
};

#endif /* SmartFoxAppConnector_hpp */
