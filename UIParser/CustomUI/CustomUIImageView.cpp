//
//  CustomUIImageView.cpp
//  GameBai69
//
//  Created by Manh Tran on 2/18/16.
//
//

#include "CustomUIImageView.hpp"

void CustomUIImageView::setSpriteFrame(cocos2d::SpriteFrame* frame)
{
    loadTexture(frame);
    setContentSize(frame->getRect().size);
}

void CustomUIImageView::attach_node(cocos2d::Node* node)
{
    addChild(node);
}