//
//  UIParserDelegate.cpp
//  1502
//
//  Created by Manh Tran on 1/15/16.
//
//

#include "UIParserDelegate.hpp"
#include "UIConstraint/UIConstraint_Resize.hpp"
#include "CustomUI/CustomUILayout.hpp"
#include "CustomUI/CustomLayoutParameter.hpp"
#include "UIParserUtils.hpp"

USING_NS_CC;
bool has_attribute(const std::string& attribute, const pugi::xml_node& node)
{
    for (auto it = node.attributes_begin(); it != node.attributes_end(); it++)
    {
        if (strcmp(it->name(), attribute.c_str()) == 0) {
            return true;
        }
    }
    return false;
}


void parseCascadeOpacity(UIParserDelegate* delegate, const pugi::char_t* value, cocos2d::Node* recent, const pugi::xml_node& node)
{
    if (recent)
    {
        recent->setCascadeOpacityEnabled(strcmp(value, "true") == 0);
    }
}

void parseRotate(UIParserDelegate* delegate, const pugi::char_t* value, cocos2d::Node* recent, const pugi::xml_node& node)
{
    if (recent)
    {
        recent->setRotation(atof(value));
    }
}

void parseX(UIParserDelegate* delegate, const pugi::char_t* value, cocos2d::Node* recent, const pugi::xml_node& node)
{
    if (recent)
    {
        recent->setPositionX(atof(value));
    }
}



void parseY(UIParserDelegate* delegate, const pugi::char_t* value, cocos2d::Node* recent, const pugi::xml_node& node)
{
    if (recent)
    {
        recent->setPositionY(atof(value));
    }
}

void parseScaleX(UIParserDelegate* delegate, const pugi::char_t* value, cocos2d::Node* recent, const pugi::xml_node& node)
{
	if (recent)
	{
		recent->setScaleX(atof(value));
	}
}

void parseScaleY(UIParserDelegate* delegate, const pugi::char_t* value, cocos2d::Node* recent, const pugi::xml_node& node)
{
	if (recent)
	{
		recent->setScaleY(atof(value));
	}
}

void parseAnchorX(UIParserDelegate* delegate, const pugi::char_t* value, cocos2d::Node* recent, const pugi::xml_node& node)
{
    if (recent)
    {
        recent->setAnchorPoint(Vec2(atof(value),recent->getAnchorPoint().y));
    }
}

void parseAnchorY(UIParserDelegate* delegate, const pugi::char_t* value, cocos2d::Node* recent, const pugi::xml_node& node)
{
    if (recent)
    {
        recent->setAnchorPoint(Vec2(recent->getAnchorPoint().x,atof(value)));
    }
}

void parseGlobalZIndex(UIParserDelegate* delegate, const pugi::char_t* value, cocos2d::Node* recent, const pugi::xml_node& node)
{
    if (recent)
    {
        recent->setGlobalZOrder(atof(value));
    }
}

void parseLocalZIndex(UIParserDelegate* delegate, const pugi::char_t* value, cocos2d::Node* recent, const pugi::xml_node& node)
{
    if (recent)
    {
        recent->setLocalZOrder(atof(value));
    }
}

void parseScale(UIParserDelegate* delegate, const pugi::char_t* value, cocos2d::Node* recent, const pugi::xml_node& node)
{
    if (recent)
    {
        recent->setScale(atof(value));
    }
}

void parseColor(UIParserDelegate* delegate, const pugi::char_t* value, cocos2d::Node* recent, const pugi::xml_node& node)
{
    if (recent)
    {
        recent->setColor(ui_parser_utils::convertColor(value));
    }
}

void parseTouch(UIParserDelegate* delegate, const pugi::char_t* value, cocos2d::Node* recent, const pugi::xml_node& node)
{
    auto recent_widget = dynamic_cast<ui::Widget*>(recent);
    if (recent_widget)
    {
        recent_widget->setTouchEnabled(strcmp(value, "true") == 0);
    }
}

void parseClip(UIParserDelegate* delegate, const pugi::char_t* value, cocos2d::Node* recent, const pugi::xml_node& node)
{
    auto recent_layout = dynamic_cast<ui::Layout*>(recent);
    if (recent_layout)
    {
        recent_layout->setClippingEnabled(strcmp(value, "true") == 0);
    }
}

void parseOpacity(UIParserDelegate* delegate, const pugi::char_t* value, cocos2d::Node* recent, const pugi::xml_node& node)
{
    if (recent)
    {
        recent->setOpacity(atoi(value));
    }
}

void parseName(UIParserDelegate* delegate, const pugi::char_t* value, cocos2d::Node* recent, const pugi::xml_node& node)
{
    if (recent)
    {
        recent->setName(value);
    }
    auto recent_widget = dynamic_cast<ui::Widget*>(recent);
    if (recent_widget && recent_widget->getLayoutParameter())
    {
        auto relative_param = dynamic_cast<ui::RelativeLayoutParameter*>(recent_widget->getLayoutParameter());
        if (relative_param)
        {
            relative_param->setRelativeName(value);
        }
    }
}

void parseRelativeTo(UIParserDelegate* delegate, const pugi::char_t* value, cocos2d::Node* recent, const pugi::xml_node& node)
{
    auto recent_widget = dynamic_cast<ui::Widget*>(recent);
    if (recent_widget && recent_widget->getLayoutParameter())
    {
        auto relative_param = dynamic_cast<ui::RelativeLayoutParameter*>(recent_widget->getLayoutParameter());
        if (relative_param)
        {
            relative_param->setRelativeToWidgetName(value);
        }
    }
}

void parseWidth(UIParserDelegate* delegate, const pugi::char_t* value, cocos2d::Node* recent, const pugi::xml_node& node)
{
    if (strcmp(value, "match_parent") == 0)
    {
        delegate->sendData(UIConstraint_Resize_Match_Parent_Width::create(recent), false);
    }
    else if (strcmp(value, "wrap_content") == 0)
    {
        delegate->sendData(UIConstraint_Resize_Wrap_Content_Width::create(recent), false);
    }
    else if(ui_parser_utils::isNumber(value))
    {
        if (recent)
        {
            recent->setContentSize(Size(atof(value), recent->getContentSize().height));
        }
    }
}

void parseHeight(UIParserDelegate* delegate, const pugi::char_t* value, cocos2d::Node* recent, const pugi::xml_node& node)
{
    if (strcmp(value, "match_parent") == 0)
    {
        delegate->sendData(UIConstraint_Resize_Match_Parent_Height::create(recent), false);
    }
    else if (strcmp(value, "wrap_content") == 0)
    {
        delegate->sendData(UIConstraint_Resize_Wrap_Content_Height::create(recent), false);
    }
    else if (strcmp(value, "iosbar") == 0)
    {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        if (recent)
        {
            auto v = Director::getInstance()->convertToGL(Vec2(0, Director::getInstance()->getOpenGLView()->isRetinaDisplay() ? 40 : 20));
            float top_pad = Director::getInstance()->getVisibleSize().height - v.y;
            recent->setContentSize(Size(recent->getContentSize().width, top_pad));
        }
#endif
    }
    else if(ui_parser_utils::isNumber(value))
    {
        if (recent) {
            recent->setContentSize(Size(recent->getContentSize().width, atof(value)));
        }
    }
}

void parsePaddingLeft(UIParserDelegate* delegate, const pugi::char_t* value, cocos2d::Node* recent, const pugi::xml_node& node)
{
    auto recent_widget = dynamic_cast<ui::Widget*>(recent);
    if (recent_widget)
    {
        auto customparam = dynamic_cast<CustomLayoutParamaterPadding*>(recent_widget->getLayoutParameter());
        if (!customparam)
        {
            auto param = CustomRelativeLayoutParameter::create();
            recent_widget->setLayoutParameter(param);
            customparam = param;
        }
        if (customparam)
        {
            if (ui_parser_utils::isNumber(value))
            {
                customparam->_ui_padding._left += atof(value);
            }
            else if(strcmp(value, "iosbar") == 0)
            {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
                auto v = Director::getInstance()->convertToGL(Vec2(0, Director::getInstance()->getOpenGLView()->isRetinaDisplay() ? 40 : 20));
                float top_pad = Director::getInstance()->getVisibleSize().height - v.y;
                customparam->_ui_padding._left += top_pad;
#endif
            }
        }
    }
}

void parsePaddingRight(UIParserDelegate* delegate, const pugi::char_t* value, cocos2d::Node* recent, const pugi::xml_node& node)
{
    auto recent_widget = dynamic_cast<ui::Widget*>(recent);
    if (recent_widget)
    {
        auto customparam = dynamic_cast<CustomLayoutParamaterPadding*>(recent_widget->getLayoutParameter());
        if (!customparam)
        {
            auto param = CustomRelativeLayoutParameter::create();
            recent_widget->setLayoutParameter(param);
            customparam = param;
        }
        if (customparam)
        {
            if (ui_parser_utils::isNumber(value))
            {
                customparam->_ui_padding._right += atof(value);
            }
            else if(strcmp(value, "iosbar") == 0)
            {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
                auto v = Director::getInstance()->convertToGL(Vec2(0, Director::getInstance()->getOpenGLView()->isRetinaDisplay() ? 40 : 20));
                float top_pad = Director::getInstance()->getVisibleSize().height - v.y;
                customparam->_ui_padding._right += top_pad;
#endif
            }
        }
    }
}

void parsePaddingTop(UIParserDelegate* delegate, const pugi::char_t* value, cocos2d::Node* recent, const pugi::xml_node& node)
{
    auto recent_widget = dynamic_cast<ui::Widget*>(recent);
    if (recent_widget)
    {
        auto customparam = dynamic_cast<CustomLayoutParamaterPadding*>(recent_widget->getLayoutParameter());
        if (!customparam)
        {
            auto param = CustomRelativeLayoutParameter::create();
            recent_widget->setLayoutParameter(param);
            customparam = param;
        }
        if (customparam)
        {
            if (ui_parser_utils::isNumber(value))
            {
                customparam->_ui_padding._top += atof(value);
            }
            else if(strcmp(value, "iosbar") == 0)
            {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
                auto v = Director::getInstance()->convertToGL(Vec2(0, Director::getInstance()->getOpenGLView()->isRetinaDisplay() ? 40 : 20));
                float top_pad = Director::getInstance()->getVisibleSize().height - v.y;
                customparam->_ui_padding._top += top_pad;
#endif
            }
        }
    }
}

void parsePaddingBottom(UIParserDelegate* delegate, const pugi::char_t* value, cocos2d::Node* recent, const pugi::xml_node& node)
{
    auto recent_widget = dynamic_cast<ui::Widget*>(recent);
    if (recent_widget)
    {
        auto customparam = dynamic_cast<CustomLayoutParamaterPadding*>(recent_widget->getLayoutParameter());
        if (!customparam)
        {
            auto param = CustomRelativeLayoutParameter::create();
            recent_widget->setLayoutParameter(param);
            customparam = param;
        }
        if (customparam)
        {
            if (ui_parser_utils::isNumber(value))
            {
                customparam->_ui_padding._bottom += atof(value);
            }
            else if(strcmp(value, "iosbar") == 0)
            {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
                auto v = Director::getInstance()->convertToGL(Vec2(0, Director::getInstance()->getOpenGLView()->isRetinaDisplay() ? 40 : 20));
                float top_pad = Director::getInstance()->getVisibleSize().height - v.y;
                customparam->_ui_padding._bottom += top_pad;
#endif
            }
        }
    }
}

void parseMarginLeft(UIParserDelegate* delegate, const pugi::char_t* value, cocos2d::Node* recent, const pugi::xml_node& node)
{
    auto recent_widget = dynamic_cast<ui::Widget*>(recent);
    if (recent_widget && recent_widget->getLayoutParameter())
    {
        ui::Margin margin = recent_widget->getLayoutParameter()->getMargin();
        if (ui_parser_utils::isNumber(value))
        {
            margin.left += atof(value);
        }
        else if(strcmp(value, "iosbar") == 0)
        {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
            auto v = Director::getInstance()->convertToGL(Vec2(0, Director::getInstance()->getOpenGLView()->isRetinaDisplay() ? 40 : 20));
            float top_pad = Director::getInstance()->getVisibleSize().height - v.y;
            margin.left += top_pad;
#endif
        }
        recent_widget->getLayoutParameter()->setMargin(margin);
    }
}

void parseMarginRight(UIParserDelegate* delegate, const pugi::char_t* value, cocos2d::Node* recent, const pugi::xml_node& node)
{
    auto recent_widget = dynamic_cast<ui::Widget*>(recent);
    if (recent_widget && recent_widget->getLayoutParameter())
    {
        ui::Margin margin = recent_widget->getLayoutParameter()->getMargin();
        if (ui_parser_utils::isNumber(value))
        {
            margin.right += atof(value);
        }
        else if(strcmp(value, "iosbar") == 0)
        {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
                auto v = Director::getInstance()->convertToGL(Vec2(0, Director::getInstance()->getOpenGLView()->isRetinaDisplay() ? 40 : 20));
                float top_pad = Director::getInstance()->getVisibleSize().height - v.y;
                margin.right += top_pad;
#endif
        }
        
        recent_widget->getLayoutParameter()->setMargin(margin);
    }
}

void parseMarginTop(UIParserDelegate* delegate, const pugi::char_t* value, cocos2d::Node* recent, const pugi::xml_node& node)
{
    auto recent_widget = dynamic_cast<ui::Widget*>(recent);
    if (recent_widget && recent_widget->getLayoutParameter())
    {
        ui::Margin margin = recent_widget->getLayoutParameter()->getMargin();
        if (ui_parser_utils::isNumber(value))
        {
             margin.top += atof(value);
        }
        else if(strcmp(value, "iosbar") == 0)
        {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
            auto v = Director::getInstance()->convertToGL(Vec2(0, Director::getInstance()->getOpenGLView()->isRetinaDisplay() ? 40 : 20));
            float top_pad = Director::getInstance()->getVisibleSize().height - v.y;
            margin.top += top_pad;
#endif
        }
        recent_widget->getLayoutParameter()->setMargin(margin);
    }
}

void parseMarginBottom(UIParserDelegate* delegate, const pugi::char_t* value, cocos2d::Node* recent, const pugi::xml_node& node)
{
    auto recent_widget = dynamic_cast<ui::Widget*>(recent);
    if (recent_widget && recent_widget->getLayoutParameter())
    {
        ui::Margin margin = recent_widget->getLayoutParameter()->getMargin();
        if (ui_parser_utils::isNumber(value))
        {
            margin.bottom += atof(value);
        }
        else if(strcmp(value, "iosbar") == 0)
        {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
            auto v = Director::getInstance()->convertToGL(Vec2(0, Director::getInstance()->getOpenGLView()->isRetinaDisplay() ? 40 : 20));
            float top_pad = Director::getInstance()->getVisibleSize().height - v.y;
            margin.bottom += top_pad;
#endif
        }
        recent_widget->getLayoutParameter()->setMargin(margin);
    }
}

void parseAlign(UIParserDelegate* delegate, const pugi::char_t* value, cocos2d::Node* recent, const pugi::xml_node& node)
{
    ui::Layout* layout_parent = nullptr;
    if (recent)
    {
        layout_parent = dynamic_cast<ui::Layout*>(recent->getParent());
    }
    
    auto recent_widget = dynamic_cast<ui::Widget*>(recent);
    if (recent_widget && recent_widget->getLayoutParameter())
    {
        auto type = recent_widget->getLayoutParameter()->getLayoutType();
        switch (type) {
            case cocos2d::ui::LayoutParameter::Type::RELATIVE:
            {
                auto param = dynamic_cast<ui::RelativeLayoutParameter*>(recent_widget->getLayoutParameter());
                if (strcmp(value, "center") == 0)
                {
                    param->setAlign(ui::RelativeLayoutParameter::RelativeAlign::CENTER_IN_PARENT);
                }
                else if (strcmp(value, "top_left") == 0)
                {
                    param->setAlign(ui::RelativeLayoutParameter::RelativeAlign::PARENT_TOP_LEFT);
                }
                else if (strcmp(value, "top_right") == 0)
                {
                    param->setAlign(ui::RelativeLayoutParameter::RelativeAlign::PARENT_TOP_RIGHT);
                }
                else if (strcmp(value, "top_center_horizontal") == 0)
                {
                    param->setAlign(ui::RelativeLayoutParameter::RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL);
                }
                else if (strcmp(value, "bottom_center_horizontal") == 0)
                {
                    param->setAlign(ui::RelativeLayoutParameter::RelativeAlign::PARENT_BOTTOM_CENTER_HORIZONTAL);
                }
                else if (strcmp(value, "left_bottom") == 0)
                {
                    param->setAlign(ui::RelativeLayoutParameter::RelativeAlign::PARENT_LEFT_BOTTOM);
                }
                else if (strcmp(value, "right_bottom") == 0)
                {
                    param->setAlign(ui::RelativeLayoutParameter::RelativeAlign::PARENT_RIGHT_BOTTOM);
                }
                else if (strcmp(value, "left_center_vertical") == 0)
                {
                    param->setAlign(ui::RelativeLayoutParameter::RelativeAlign::PARENT_LEFT_CENTER_VERTICAL);
                }
                else if (strcmp(value, "right_center_vertical") == 0)
                {
                    param->setAlign(ui::RelativeLayoutParameter::RelativeAlign::PARENT_RIGHT_CENTER_VERTICAL);
                }
                else if (strcmp(value, "location_above_center") == 0)
                {
                    param->setAlign(ui::RelativeLayoutParameter::RelativeAlign::LOCATION_ABOVE_CENTER);
                }
                else if (strcmp(value, "location_above_left") == 0)
                {
                    param->setAlign(ui::RelativeLayoutParameter::RelativeAlign::LOCATION_ABOVE_LEFTALIGN);
                }
                else if (strcmp(value, "location_above_right") == 0)
                {
                    param->setAlign(ui::RelativeLayoutParameter::RelativeAlign::LOCATION_ABOVE_RIGHTALIGN);
                }
                else if (strcmp(value, "location_below_center") == 0)
                {
                    param->setAlign(ui::RelativeLayoutParameter::RelativeAlign::LOCATION_BELOW_CENTER);
                }
                else if (strcmp(value, "location_below_left") == 0)
                {
                    param->setAlign(ui::RelativeLayoutParameter::RelativeAlign::LOCATION_BELOW_LEFTALIGN);
                }
                else if (strcmp(value, "location_below_right") == 0)
                {
                    param->setAlign(ui::RelativeLayoutParameter::RelativeAlign::LOCATION_BELOW_RIGHTALIGN);
                }
                else if (strcmp(value, "location_left_of_center") == 0)
                {
                    param->setAlign(ui::RelativeLayoutParameter::RelativeAlign::LOCATION_LEFT_OF_CENTER);
                }
                else if (strcmp(value, "location_left_of_bottom") == 0)
                {
                    param->setAlign(ui::RelativeLayoutParameter::RelativeAlign::LOCATION_LEFT_OF_BOTTOMALIGN);
                }
                else if (strcmp(value, "location_left_of_top") == 0)
                {
                    param->setAlign(ui::RelativeLayoutParameter::RelativeAlign::LOCATION_LEFT_OF_TOPALIGN);
                }
                else if (strcmp(value, "location_right_of_center") == 0)
                {
                    param->setAlign(ui::RelativeLayoutParameter::RelativeAlign::LOCATION_RIGHT_OF_CENTER);
                }
                else if (strcmp(value, "location_right_of_bottom") == 0)
                {
                    param->setAlign(ui::RelativeLayoutParameter::RelativeAlign::LOCATION_RIGHT_OF_BOTTOMALIGN);
                }
                else if (strcmp(value, "location_right_of_top") == 0)
                {
                    param->setAlign(ui::RelativeLayoutParameter::RelativeAlign::LOCATION_RIGHT_OF_TOPALIGN);
                }
            }
                break;
            case cocos2d::ui::LayoutParameter::Type::LINEAR:
            {
                auto param = dynamic_cast<ui::LinearLayoutParameter*>(recent_widget->getLayoutParameter());
                if (strcmp(value, "center") == 0)
                {
                    if (layout_parent)
                    {
                        if (layout_parent->getLayoutType() == ui::Layout::Type::VERTICAL)
                        {
                            param->setGravity(ui::LinearLayoutParameter::LinearGravity::CENTER_HORIZONTAL);
                        }
                        else param->setGravity(ui::LinearLayoutParameter::LinearGravity::CENTER_VERTICAL);
                    }
                    
                }
                else if (strcmp(value, "left") == 0)
                {
                    param->setGravity(ui::LinearLayoutParameter::LinearGravity::LEFT);
                }
                else if (strcmp(value, "right") == 0)
                {
                    param->setGravity(ui::LinearLayoutParameter::LinearGravity::RIGHT);
                }
                else if (strcmp(value, "top") == 0)
                {
                    param->setGravity(ui::LinearLayoutParameter::LinearGravity::TOP);
                }
                else if (strcmp(value, "bottom") == 0)
                {
                    param->setGravity(ui::LinearLayoutParameter::LinearGravity::BOTTOM);
                }
            }
                break;
            case cocos2d::ui::LayoutParameter::Type::NONE:
                
                break;
            default:
                break;
        }
    }
}

void parseTouchDelegate(UIParserDelegate* delegate, const pugi::char_t* value, cocos2d::Node* recent, const pugi::xml_node& node)
{
    auto layout = dynamic_cast<CustomUILayout*>(recent);
    if (layout)
    {
        if (delegate->_parser->getTouchDelegates()->at(value))
        {
            layout->setOnTouchDelegate(delegate->_parser->getTouchDelegates()->at(value));
        }
        else if(delegate->_parser->_linked_parent)
        {
            layout->setOnTouchDelegate(delegate->_parser->_linked_parent->getTouchDelegates()->at(value));
        }
    }
}

void parseBindTouch(UIParserDelegate* delegate, const pugi::char_t* value, cocos2d::Node* recent, const pugi::xml_node& node)
{
    CustomUITouchDelegateComponent* component = nullptr;
    if (recent)
    {
        component = dynamic_cast<CustomUITouchDelegateComponent*>(recent->getComponent("touchDelegates"));
    }
    if (component)
    {
        std::vector<std::string> pairs;
        ui_parser_utils::split(value, ';', pairs);
        for (auto& pair : pairs)
        {
            std::vector<std::string> content;
            ui_parser_utils::split(pair, '=', content);
            CustomUITouchDelegate* down = component->_delegates.at(content[0]);
            CustomUITouchDelegate* up   = delegate->_parser->getTouchDelegates()->at(content[1]);
            if (up && down)
            {
                down->setForward(up);
            }
            else if(!up && down && delegate->_parser->_linked_parent)
            {
                up = delegate->_parser->_linked_parent->getTouchDelegates()->at(content[1]);
                if (up)
                {
                    down->setForward(up);
                }
            }
        }
    }
}

void parseCloneKey(UIParserDelegate* delegate, const pugi::char_t* value, cocos2d::Node* recent, const pugi::xml_node& node)
{
    if (delegate->_parser->getHashXmlNodes()->find(value) == delegate->_parser->getHashXmlNodes()->end())
    {
        delegate->_parser->getHashXmlNodes()->insert(std::make_pair(value, node));
    }
}

void parseHashKey(UIParserDelegate* delegate, const pugi::char_t* value, cocos2d::Node* recent, const pugi::xml_node& node)
{
    if (recent)
    {
        if (!delegate->_parser->getHasNodes()->at(value))
        {
            delegate->_parser->getHasNodes()->insert(value, recent);
        }
    }
}

void parseSwallow(UIParserDelegate* delegate, const pugi::char_t* value, cocos2d::Node* recent, const pugi::xml_node& node)
{
    auto layout = dynamic_cast<CustomUILayout*>(recent);
    if (layout)
    {
        layout->setNeedSwallow(strcmp(value, "true") == 0);
    }
}

void parseVisible(UIParserDelegate* delegate, const pugi::char_t* value, cocos2d::Node* recent, const pugi::xml_node& node)
{
    if (recent)
    {
        recent->setVisible(strcmp(value, "true") == 0);
    }
}

std::unordered_map<std::string, std::function<void(UIParserDelegate*, const pugi::char_t*, cocos2d::Node*,const pugi::xml_node&)>> _delegates;
bool _setup_ = false;

void UIParserDelegate::processCommonConstraint(const pugi::xml_node& node, cocos2d::Node* recent)
{
    if ( ! recent)
    {
        return;
    }
    
    if (!_setup_)
    {
        _setup_ = true;
        _delegates.insert(std::make_pair("visible", parseVisible));
        _delegates.insert(std::make_pair("rotate", parseRotate));
        _delegates.insert(std::make_pair("scale", parseScale));
        _delegates.insert(std::make_pair("color", parseColor));
        _delegates.insert(std::make_pair("touch", parseTouch));
        _delegates.insert(std::make_pair("clip", parseClip));
        _delegates.insert(std::make_pair("opacity", parseOpacity));
        _delegates.insert(std::make_pair("name", parseName));
        _delegates.insert(std::make_pair("relative_to", parseRelativeTo));
        _delegates.insert(std::make_pair("width", parseWidth));
        _delegates.insert(std::make_pair("height", parseHeight));
        _delegates.insert(std::make_pair("margin_left", parseMarginLeft));
        _delegates.insert(std::make_pair("margin_right", parseMarginRight));
        _delegates.insert(std::make_pair("margin_top", parseMarginTop));
        _delegates.insert(std::make_pair("margin_bottom", parseMarginBottom));
        _delegates.insert(std::make_pair("padding_left", parsePaddingLeft));
        _delegates.insert(std::make_pair("padding_right", parsePaddingRight));
        _delegates.insert(std::make_pair("padding_top", parsePaddingTop));
        _delegates.insert(std::make_pair("padding_bottom", parsePaddingBottom));
        _delegates.insert(std::make_pair("align", parseAlign));
        _delegates.insert(std::make_pair("touchdelegate", parseTouchDelegate));
        _delegates.insert(std::make_pair("bindtouch", parseBindTouch));
        _delegates.insert(std::make_pair("swallow", parseSwallow));
        _delegates.insert(std::make_pair("clonekey", parseCloneKey));
        _delegates.insert(std::make_pair("hashkey", parseHashKey));
        _delegates.insert(std::make_pair("x", parseX));
        _delegates.insert(std::make_pair("y", parseY));
		_delegates.insert(std::make_pair("scale-x", parseScaleX));
		_delegates.insert(std::make_pair("scale-y", parseScaleY));
        _delegates.insert(std::make_pair("anchor-x", parseAnchorX));
        _delegates.insert(std::make_pair("anchor-y", parseAnchorY));
        _delegates.insert(std::make_pair("globalZ", parseGlobalZIndex));
        _delegates.insert(std::make_pair("local_z", parseLocalZIndex));
        _delegates.insert(std::make_pair("cascade_opacity", parseCascadeOpacity));
    }
    
    for (auto it = node.attributes_begin(); it != node.attributes_end(); it++)
    {
        if (_delegates.find(it->name()) != _delegates.end())
        {
            _delegates.at(it->name())(this, it->value(), recent, node);
        }
        else
        {
            auto customuidata = dynamic_cast<CustomUIData*>(recent);
            if (customuidata)
            {
                customuidata->setCustomAttribute(it->name(), it->value());
            }
        }
    }
}