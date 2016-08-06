//
//  CustomUIEditBox.hpp
//  Busino
//
//  Created by Manh Tran on 1/19/16.
//
//

#ifndef CustomUIEditBox_hpp
#define CustomUIEditBox_hpp

#include "ui/UIEditBox/UIEditBox.h"
#include "CustomUIData.h"
#include "CustomUIInterface.hpp"

class CustomUIEditBox : public cocos2d::ui::EditBox, public CustomUIData, public CustomUIInterface
{
public:
    static CustomUIEditBox* create(const cocos2d::Size& size, const std::string& scale9Image);
    static CustomUIEditBox* create(const cocos2d::Size& size, cocos2d::ui::Scale9Sprite* sprite);
    virtual void setContentSize(const cocos2d::Size& size) override;
    virtual std::string getString();
    virtual void attach_node(cocos2d::Node* node);
};

#endif /* CustomUIEditBox_hpp */
