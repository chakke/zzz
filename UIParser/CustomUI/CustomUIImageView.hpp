//
//  CustomUIImageView.hpp
//  GameBai69
//
//  Created by Manh Tran on 2/18/16.
//
//

#ifndef CustomUIImageView_hpp
#define CustomUIImageView_hpp

#include "ui/UIImageView.h"
#include "CustomUIData.h"
#include "CustomUIInterface.hpp"

class CustomUIImageView : public cocos2d::ui::ImageView, public CustomUIData, public CustomUIInterface
{
public:
    CREATE_FUNC(CustomUIImageView);
    
    void setSpriteFrame(cocos2d::SpriteFrame* frame);
    virtual void attach_node(cocos2d::Node* node);
};

#endif /* CustomUIImageView_hpp */
