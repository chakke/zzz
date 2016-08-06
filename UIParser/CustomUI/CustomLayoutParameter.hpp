//
//  CustomLayoutParameter.hpp
//  Busino
//
//  Created by Manh Tran on 1/22/16.
//
//

#ifndef CustomLayoutParameter_hpp
#define CustomLayoutParameter_hpp

#include "cocos2d.h"
#include "ui/UILayout.h"

class UIPadding
{
public:
    float _top;
    float _bottom;
    float _left;
    float _right;
    
    UIPadding();
    UIPadding(float top, float bottom, float left, float right);
    UIPadding(const UIPadding& other);
    UIPadding& operator= (const UIPadding& other);
    void setPadding(float l, float t, float r, float b);
    bool equals(const UIPadding& target) const;
    static const UIPadding ZERO;
};

class CustomLayoutParamaterPadding
{
public:
    UIPadding _ui_padding;
};

class CustomLinearLayoutParameter : public cocos2d::ui::LinearLayoutParameter, public CustomLayoutParamaterPadding
{
public:
    static CustomLinearLayoutParameter* create();
    //override functions.
    virtual LayoutParameter* createCloneInstance() override;
    virtual void copyProperties(LayoutParameter* model) override;
};

class CustomRelativeLayoutParameter : public cocos2d::ui::RelativeLayoutParameter, public CustomLayoutParamaterPadding
{
public:
    static CustomRelativeLayoutParameter* create();
    //override functions.
    virtual LayoutParameter* createCloneInstance() override;
    virtual void copyProperties(LayoutParameter* model) override;
};

#endif /* CustomLayoutParameter_hpp */
