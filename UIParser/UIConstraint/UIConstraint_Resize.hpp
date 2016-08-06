//
//  UIConstraint_Resize.hpp
//  Busino
//
//  Created by Manh Tran on 1/16/16.
//
//

#ifndef UIConstraint_Resize_hpp
#define UIConstraint_Resize_hpp

#include "UIConstraint.hpp"

class UIConstraint_Resize_Match_Parent_Width : public UIConstraint
{
public:
    CREATE_UI_CONSTRAINT(UIConstraint_Resize_Match_Parent_Width);
    
    virtual void update(float delta);
};

class UIConstraint_Resize_Match_Parent_Height : public UIConstraint
{
public:
    CREATE_UI_CONSTRAINT(UIConstraint_Resize_Match_Parent_Height);
    
    virtual void update(float delta);
};

class UIConstraint_Resize_Wrap_Content_Width : public UIConstraint
{
public:
    CREATE_UI_CONSTRAINT(UIConstraint_Resize_Wrap_Content_Width);
    
    virtual void update(float delta);
};

class UIConstraint_Resize_Wrap_Content_Height : public UIConstraint
{
public:
    CREATE_UI_CONSTRAINT(UIConstraint_Resize_Wrap_Content_Height);
    
    virtual void update(float delta);
};

class UIConstraint_Resize_ListView_Height : public UIConstraint
{
public:
    CREATE_UI_CONSTRAINT(UIConstraint_Resize_ListView_Height);
    
    virtual void update(float delta);
};

class UIConstraint_Resize_ListView_Width : public UIConstraint
{
public:
    CREATE_UI_CONSTRAINT(UIConstraint_Resize_ListView_Width);
    
    virtual void update(float delta);
};

#endif /* UIConstraint_Resize_hpp */
