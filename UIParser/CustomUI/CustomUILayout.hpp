//
//  CustomUILayout.hpp
//  Busino
//
//  Created by Manh Tran on 1/18/16.
//
//

#ifndef CustomUILayout_hpp
#define CustomUILayout_hpp

#include "cocos2d.h"
#include "ui/UILayout.h"
#include "CustomUIData.h"
#include "CustomUITouchDelegate.hpp"
#include "CustomUIImageView.hpp"
#include "../../CustomUI/CustomOneTouchUI.h"
#include "CustomUIInterface.hpp"

class CustomUILayout : public CustomOneTouchLayout, public CustomUIData, public CustomUIInterface
{
public:
    CREATE_FUNC(CustomUILayout);
    CustomUILayout();
    virtual ~CustomUILayout();
    virtual bool init();
    
    void setOnTouchDelegate(CustomUITouchDelegate* delegate);
    
    void onTouch(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
    void customSupplyTheLayoutParameterLackToChild(cocos2d::ui::Widget *child);
    
    virtual void setTouchEnabled(bool enabled);
    virtual void setNeedSwallow(bool);

    virtual void addChild(cocos2d::Node* child);
    virtual void addChild(cocos2d::Node * child, int localZOrder);
    virtual void addChild(cocos2d::Node *child, int zOrder, int tag);
    virtual void addChild(cocos2d::Node* child, int zOrder, const std::string &name);
    
    virtual void attach_node(cocos2d::Node* node);
    
    std::vector<std::function<void(cocos2d::Node*)>> _down_delegates;
    std::vector<std::function<void(cocos2d::Node*)>> _move_delegates;
    std::vector<std::function<void(cocos2d::Node*)>> _end_delegates;
    std::vector<std::function<void(cocos2d::Node*)>> _cancel_delegates;
    
    CustomUITouchDelegate* _onTouchDelegate;
    
    bool isNeedSwallow() { return _need_swallow; }
    virtual void setContentSize(const cocos2d::Size& contentSize) override;
    
    void setCustomBackground(const std::string& image);
    void setCustomBackground(cocos2d::SpriteFrame* frame);
    void setCustomBackgroundScale9(const bool& scale9);
    void setCustomBackgroundCap(const cocos2d::Rect& cap);
protected:
    void requireBackground();
    virtual void onSizeChanged() override;
private:
    bool _need_swallow;
    CustomUIImageView* _custom_background;
};

#endif /* CustomUILayout_hpp */
