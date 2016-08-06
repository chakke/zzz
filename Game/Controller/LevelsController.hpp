#pragma once
#include "../../AppController/Controller.hpp"
#include "ui/CocosGUI.h"
class LevelsController : public Controller
{
public:
    CREATE_FUNC(LevelsController);
    
    virtual bool init();
    
    virtual void onRemove();
    
    virtual void onLinked();
    
    virtual void update(float delta);
  
	virtual void onTouchLevel(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
private:

};
