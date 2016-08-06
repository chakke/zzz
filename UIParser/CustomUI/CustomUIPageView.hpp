//
//  CustomUIPageView.hpp
//  GameBai69
//
//  Created by Manh Tran on 3/22/16.
//
//

#ifndef CustomUIPageView_hpp
#define CustomUIPageView_hpp

#include "ui/UIPageView.h"
#include "CustomUIData.h"
#include "CustomUIInterface.hpp"

class CustomUIPageView : public cocos2d::ui::PageView, public CustomUIData, public CustomUIInterface
{
public:
    CREATE_FUNC(CustomUIPageView);
    
    void attach_node(cocos2d::Node* node);
};

#endif /* CustomUIPageView_hpp */
