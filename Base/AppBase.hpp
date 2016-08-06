//
//  AppBase.hpp
//  TestApp
//
//  Created by Manh Tran on 12/24/15.
//
//

#ifndef AppBase_hpp
#define AppBase_hpp

#include "cocos2d.h"

template<typename T>
class AppBaseDelegate : public cocos2d::Ref
{
public:
    
    virtual void process(T* object) = 0;
};

#endif /* AppBase_hpp */
