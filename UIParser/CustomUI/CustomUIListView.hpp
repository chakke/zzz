//
//  CustomUIListView.hpp
//  GameBai69
//
//  Created by Manh Tran on 2/27/16.
//
//

#ifndef CustomUIListView_hpp
#define CustomUIListView_hpp

#include "ui/UIListView.h"
#include "CustomUIData.h"
#include "CustomUIInterface.hpp"

class CustomUIListView : public cocos2d::ui::ListView, public CustomUIData, public CustomUIInterface
{
public:
    CREATE_FUNC(CustomUIListView);
    
    void attach_node(cocos2d::Node* node);
};

#endif /* CustomUIListView_hpp */
