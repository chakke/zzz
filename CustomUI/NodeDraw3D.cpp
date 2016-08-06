//
//  NodeDraw3D.cpp
//  1502
//
//  Created by Manh Tran on 1/6/16.
//
//

#include "NodeDraw3D.hpp"

USING_NS_CC;

void Node3D::visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags)
{
    Node::visit(renderer, parentTransform, parentFlags | Node::FLAGS_RENDER_AS_3D);
//     Node::visit(renderer, parentTransform, parentFlags);
}