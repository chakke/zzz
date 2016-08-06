//
//  RefData.hpp
//  1502
//
//  Created by Manh Tran on 1/8/16.
//
//

#ifndef RefData_hpp
#define RefData_hpp

#include "cocos2d.h"

template<class T>
class VectorRef : public cocos2d::Ref
{
public:
    static VectorRef* create()
    {
        auto ret = new VectorRef<T>();
        ret->autorelease();
        return ret;
    }
    virtual ~VectorRef()
    {
        _vector.clear();
    }
    
    cocos2d::Vector<T> _vector;
};

#endif /* RefData_hpp */
