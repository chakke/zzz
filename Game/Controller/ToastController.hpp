
#ifndef ToastController_hpp
#define ToastController_hpp

#include "../../AppController/Controller.hpp"
#include "ui/CocosGUI.h"

class ToastController : public Controller
{
public:
    static ToastController* getInstance();
    
    virtual bool init();
    
    void toast(const std::string& text, const float& time);

protected : 

	cocos2d::ui::Layout* mLayout;
	cocos2d::ui::Text* mText;
};

#endif /* ToastController_hpp */
