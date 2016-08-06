//
//  NodeDraw3D.hpp
//  1502
//
//  Created by Manh Tran on 1/6/16.
//
//

#ifndef NodeDraw3D_hpp
#define NodeDraw3D_hpp

#include "cocos2d.h"

class Node3D : public cocos2d::Node
{
public:
    CREATE_FUNC(Node3D);
    
    virtual void visit(cocos2d::Renderer *renderer, const cocos2d::Mat4& parentTransform, uint32_t parentFlags);
};

#endif /* NodeDraw3D_hpp */
