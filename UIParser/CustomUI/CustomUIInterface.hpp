//
//  CustomUIInterface.hpp
//  GameBai69
//
//  Created by Manh Tran on 3/22/16.
//
//

#ifndef CustomUIInterface_hpp
#define CustomUIInterface_hpp

#include "cocos2d.h"

class CustomUIInterface
{
public:
    virtual void attach_node(cocos2d::Node* node) = 0;
};

#endif /* CustomUIInterface_hpp */
