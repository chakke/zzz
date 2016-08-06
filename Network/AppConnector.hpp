//
//  AppConnector.hpp
//  Busino
//
//  Created by Manh Tran on 1/19/16.
//
//

#ifndef AppConnector_hpp
#define AppConnector_hpp

#include "cocos2d.h"
#include "../Utils/ObserverPattern.h"
#include "../Base/AppBase.hpp"
#include "../Data/ObserverData.hpp"

//=========================================================
//                      Connector
//=========================================================
class AppConnector : public cocos2d::Ref, public Observable, public Observer
{
public:
    virtual ~AppConnector();
    
    virtual bool init() = 0;
    
    virtual void update(float delta) = 0;
    
    virtual void listen(Observer*, cocos2d::Ref*) = 0;
    
    virtual void updateServerConfig() = 0;
    
    virtual bool isUdp() = 0;
CC_CONSTRUCTOR_ACCESS:
    cocos2d::Map<int, AppBaseDelegate<network_data>*> _apiDelegates;
    cocos2d::Map<int, cocos2d::Ref*> _refMap;
};

#endif /* AppConnector_hpp */
