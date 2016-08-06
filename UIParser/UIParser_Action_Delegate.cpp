//
//  UIParser_Action_Delegate.cpp
//  Busino
//
//  Created by Manh Tran on 1/18/16.
//
//

#include "UIParser_Action_Delegate.hpp"
#include "Action/ParserAction.hpp"
#include "CustomUI/CustomUILayout.hpp"
#include "UIParserUtils.hpp"

USING_NS_CC;

class UIParserActionSequence : public UIParserActionData
{
public:
    virtual ~UIParserActionSequence()
    {
        _actions.clear();
    }
    
    virtual cocos2d::FiniteTimeAction* parse()
    {
        cocos2d::Vector<cocos2d::FiniteTimeAction*> v;
        for (auto data : _actions)
        {
            v.pushBack(data->parse());
        }
        return Sequence::create(v);
    }
    
    cocos2d::Vector<UIParserActionData*> _actions;
};

class UIParserActionSpawn : public UIParserActionData
{
public:
    virtual ~UIParserActionSpawn()
    {
        _actions.clear();
    }
    
    virtual cocos2d::FiniteTimeAction* parse()
    {
        cocos2d::Vector<cocos2d::FiniteTimeAction*> v;
        for (auto data : _actions)
        {
            v.pushBack(data->parse());
        }
        return Spawn::create(v);
    }
    
    cocos2d::Vector<UIParserActionData*> _actions;
};

class UIParserActionRepeatForever : public UIParserActionData
{
public:
    
    virtual cocos2d::FiniteTimeAction* parse()
    {
        return RepeatForever::create((ActionInterval*)_action->parse());
    }
    UIParserActionData* _action;
};

class UIParserActionMoveTo : public UIParserActionData
{
public:
    
    virtual cocos2d::FiniteTimeAction* parse()
    {
        return MoveTo::create(_time, Vec2(_x, _y));
    }
    
    float _time;
    float _x;
    float _y;
};

class UIParserActionMoveBy : public UIParserActionData
{
public:
    
    virtual cocos2d::FiniteTimeAction* parse()
    {
        return MoveBy::create(_time, Vec2(_x, _y));
    }
    
    float _time;
    float _x;
    float _y;
};


class UIParserActionFadeOut : public UIParserActionData
{
public:
    
    virtual cocos2d::FiniteTimeAction* parse()
    {
        return FadeOut::create(_time);
    }
    
    float _time;
};

class UIParserActionFadeIn : public UIParserActionData
{
public:
    
    virtual cocos2d::FiniteTimeAction* parse()
    {
        return FadeIn::create(_time);
    }
    
    float _time;
};

class UIParserActionFadeTo : public UIParserActionData
{
public:
    
    virtual cocos2d::FiniteTimeAction* parse()
    {
        return FadeTo::create(_time, _opacity);
    }
    
    float _time;
    int _opacity;
};

class UIParserActionScaleTo : public UIParserActionData
{
public:
    
    virtual cocos2d::FiniteTimeAction* parse()
    {
        return ScaleTo::create(_time, _x, _y);
    }
    
    float _time;
    float _x;
    float _y;
};

class UIParserActionScaleBy : public UIParserActionData
{
public:
    
    virtual cocos2d::FiniteTimeAction* parse()
    {
        return ScaleBy::create(_time, _x, _y);
    }
    
    float _time;
    float _x;
    float _y;
};

class UIParserActionRotateTo : public UIParserActionData
{
public:
    
    virtual cocos2d::FiniteTimeAction* parse()
    {
        return RotateTo::create(_time, _r);
    }
    
    float _time;
    float _r;
};

class UIParserActionRotateBy : public UIParserActionData
{
public:
    
    virtual cocos2d::FiniteTimeAction* parse()
    {
        return RotateBy::create(_time, _r);
    }
    
    float _time;
    float _r;
};

class UIParserActionTintTo : public UIParserActionData
{
public:
    
    virtual cocos2d::FiniteTimeAction* parse()
    {
        return TintTo::create(_time, _color);
    }
    
    float _time;
    cocos2d::Color3B _color;
};

class UIParserActionDelayTime : public UIParserActionData
{
public:
    
    virtual cocos2d::FiniteTimeAction* parse()
    {
        return DelayTime::create(_time);
    }
    
    float _time;
};

cocos2d::Node* UIParserActionDelegate::createNode(const pugi::xml_node& node)
{
    return nullptr;
}

void delegateAction(const std::string& node_id, const std::string& key, Node* current)
{
    std::vector<std::string> ids;
    ui_parser_utils::split(node_id, ':', ids);
    
    cocos2d::Node* target = current;
    for (int i = 0; i < ids.size(); i++)
    {
        if (ids[i].compare("this") != 0 && target)
        {
            target = target->getChildByName(ids[i]);
        }
    }
    
    auto action = ParserAction::getInstance()->getAction(key);
    if (target)
    {
        target->runAction(action);
    }
}

void UIParserActionDelegate::constraintWithParent(const pugi::xml_node& node, const pugi::xml_node& prev_node, cocos2d::Node* parent, cocos2d::Node* recent)
{
    std::string node_id = "";
    for (auto it = node.attributes_begin(); it != node.attributes_end(); it++)
    {
        if (strcmp(it->name(), "id") == 0)
        {
            node_id = it->value();
        }
    }
    
    _datas.clear();
    _stacks.clear();
    pugi::xml_node n = node;
    n.traverse(*this);
    
    for (auto data : _datas)
    {
        int id = _parser->_current_action;
        _parser->_current_action++;
        std::string key = StringUtils::format("%s_%d", _parser->getCurrentFile().c_str(), id);
        if ( ! ParserAction::getInstance()->hasAction(key))
        {
            auto cache = data->parse();
            ParserAction::getInstance()->setAction(key, cache);
        }
        
        if (strcmp(prev_node.name(), "touchbegan") == 0)
        {
            auto layout = dynamic_cast<CustomUILayout*>(parent);
            layout->_down_delegates.push_back([node_id, key](Node* current)
            {
                delegateAction(node_id, key, current);
            });
        }
        else if (strcmp(prev_node.name(), "touchend") == 0)
        {
            auto layout = dynamic_cast<CustomUILayout*>(parent);
            layout->_end_delegates.push_back([node_id, key](Node* current)
            {
                delegateAction(node_id, key, current);
            });
        }
        else if (strcmp(prev_node.name(), "touchmove") == 0)
        {
            auto layout = dynamic_cast<CustomUILayout*>(parent);
            layout->_move_delegates.push_back([node_id, key](Node* current)
             {
                 delegateAction(node_id, key, current);
             });
        }
        else if (strcmp(prev_node.name(), "touchcancel") == 0)
        {
            auto layout = dynamic_cast<CustomUILayout*>(parent);
            layout->_cancel_delegates.push_back([node_id, key](Node* current)
             {
                 delegateAction(node_id, key, current);
             });
        }
        else if (strcmp(prev_node.name(), "runaction") == 0)
        {
            if (parent) delegateAction(node_id, key, parent);
        }
    }
    
    _datas.clear();
    _stacks.clear();
}

// Callback that is called when traversal begins
bool UIParserActionDelegate::begin(pugi::xml_node& node)
{
    return true;
}

// Callback that is called for each node traversed
bool UIParserActionDelegate::for_each(pugi::xml_node& node)
{
    UIParserActionData* data = nullptr;
    if (strcmp("fadeout", node.name()) == 0)
    {
        float time = 0;
        for (auto it = node.attributes_begin(); it != node.attributes_end(); it++)
        {
            if (strcmp(it->name(), "time") == 0)
            {
                time = atof(it->value());
            }
        }
        auto fadeout = new UIParserActionFadeOut();
        fadeout->_time = time;
        data = fadeout;
    }
    else if (strcmp("fadein", node.name()) == 0)
    {
        float time = 0;
        for (auto it = node.attributes_begin(); it != node.attributes_end(); it++)
        {
            if (strcmp(it->name(), "time") == 0)
            {
                time = atof(it->value());
            }
        }
        auto fadeto = new UIParserActionFadeIn();
        fadeto->_time = time;
        data = fadeto;
    }
    else if (strcmp("fadeto", node.name()) == 0)
    {
        float time = 0;
        int opacity = 0;
        for (auto it = node.attributes_begin(); it != node.attributes_end(); it++)
        {
            if (strcmp(it->name(), "time") == 0)
            {
                time = atof(it->value());
            }
            else if (strcmp(it->name(), "to") == 0)
            {
                opacity = atof(it->value());
            }
        }
        auto action = new UIParserActionFadeTo();
        action->_time = time;
        action->_opacity = opacity;
        data = action;
    }
    else if (strcmp("moveto", node.name()) == 0)
    {
        float time = 0;
        float x = 0;
        float y = 0;
        for (auto it = node.attributes_begin(); it != node.attributes_end(); it++)
        {
            if (strcmp(it->name(), "time") == 0)
            {
                time = atof(it->value());
            }
            else if (strcmp(it->name(), "x") == 0)
            {
                x = atof(it->value());
            }
            else if (strcmp(it->name(), "y") == 0)
            {
                y = atof(it->value());
            }
        }
        auto action = new UIParserActionMoveTo();
        action->_time = time;
        action->_x = x;
        action->_y = y;
        data = action;
    }
    else if (strcmp("moveby", node.name()) == 0)
    {
        float time = 0;
        float x = 0;
        float y = 0;
        for (auto it = node.attributes_begin(); it != node.attributes_end(); it++)
        {
            if (strcmp(it->name(), "time") == 0)
            {
                time = atof(it->value());
            }
            else if (strcmp(it->name(), "x") == 0)
            {
                x = atof(it->value());
            }
            else if (strcmp(it->name(), "y") == 0)
            {
                y = atof(it->value());
            }
        }
        auto action = new UIParserActionMoveBy();
        action->_time = time;
        action->_x = x;
        action->_y = y;
        data = action;
    }
    else if (strcmp("scaleto", node.name()) == 0)
    {
        float time = 0;
        float x = 0;
        float y = 0;
        for (auto it = node.attributes_begin(); it != node.attributes_end(); it++)
        {
            if (strcmp(it->name(), "time") == 0)
            {
                time = atof(it->value());
            }
            else if (strcmp(it->name(), "x") == 0)
            {
                x = atof(it->value());
            }
            else if (strcmp(it->name(), "y") == 0)
            {
                y = atof(it->value());
            }
        }
        auto action = new UIParserActionScaleTo();
        action->_time = time;
        action->_x = x;
        action->_y = y;
        data = action;
    }
    else if (strcmp("scaleby", node.name()) == 0)
    {
        float time = 0;
        float x = 0;
        float y = 0;
        for (auto it = node.attributes_begin(); it != node.attributes_end(); it++)
        {
            if (strcmp(it->name(), "time") == 0)
            {
                time = atof(it->value());
            }
            else if (strcmp(it->name(), "x") == 0)
            {
                x = atof(it->value());
            }
            else if (strcmp(it->name(), "y") == 0)
            {
                y = atof(it->value());
            }
        }
        auto action = new UIParserActionScaleBy();
        action->_time = time;
        action->_x = x;
        action->_y = y;
        data = action;
    }
    else if (strcmp("rotateto", node.name()) == 0)
    {
        float time = 0;
        float r = 0;
        for (auto it = node.attributes_begin(); it != node.attributes_end(); it++)
        {
            if (strcmp(it->name(), "time") == 0)
            {
                time = atof(it->value());
            }
            else if (strcmp(it->name(), "r") == 0)
            {
                r = atof(it->value());
            }
        }
        auto action = new UIParserActionRotateTo();
        action->_time = time;
        action->_r = r;
        data = action;
    }
    else if (strcmp("rotateby", node.name()) == 0)
    {
        float time = 0;
        float r = 0;
        for (auto it = node.attributes_begin(); it != node.attributes_end(); it++)
        {
            if (strcmp(it->name(), "time") == 0)
            {
                time = atof(it->value());
            }
            else if (strcmp(it->name(), "r") == 0)
            {
                r = atof(it->value());
            }
        }
        auto action = new UIParserActionRotateBy();
        action->_time = time;
        action->_r = r;
        data = action;
    }
    else if (strcmp("tintto", node.name()) == 0)
    {
        float time = 0;
        cocos2d::Color3B color = Color3B::WHITE;
        for (auto it = node.attributes_begin(); it != node.attributes_end(); it++)
        {
            if (strcmp(it->name(), "time") == 0)
            {
                time = atof(it->value());
            }
            else if (strcmp(it->name(), "color") == 0)
            {
                color = ui_parser_utils::convertColor(it->value());
            }
        }
        auto action = new UIParserActionTintTo();
        action->_time = time;
        action->_color = color;
        data = action;
    }
    else if (strcmp("delay", node.name()) == 0)
    {
        float time = 0;
        for (auto it = node.attributes_begin(); it != node.attributes_end(); it++)
        {
            if (strcmp(it->name(), "time") == 0)
            {
                time = atof(it->value());
            }
        }
        auto action = new UIParserActionDelayTime();
        action->_time = time;
        data = action;
    }
    else if(strcmp("sequence", node.name()) == 0)
    {
        data = new UIParserActionSequence();
    }
    else if(strcmp("spawn", node.name()) == 0)
    {
        data = new UIParserActionSpawn();
    }
    else if(strcmp("repeatforever", node.name()) == 0)
    {
        data = new UIParserActionRepeatForever();
    }
    
    if (data)
    {
        if (_stacks.size() == 0)
        {
            _stacks.pushBack(data);
            _datas.pushBack(data);
        }
        else
        {
            auto sequence = dynamic_cast<UIParserActionSequence*>(_stacks.back());
            if (sequence)
            {
                sequence->_actions.pushBack(data);
            }
            
            auto spawn = dynamic_cast<UIParserActionSpawn*>(_stacks.back());
            if (spawn)
            {
                spawn->_actions.pushBack(data);
            }
            
            auto repeatforever = dynamic_cast<UIParserActionRepeatForever*>(_stacks.back());
            if (repeatforever)
            {
                repeatforever->_action = data;
            }
            
            _stacks.pushBack(data);
        }
        _just_parse = true;
    }
    else
    {
        _just_parse = false;
    }
    return true;
}

bool UIParserActionDelegate::end_each(pugi::xml_node& node)
{
    if(_just_parse) _stacks.popBack();
    return true;
}

// Callback that is called when traversal ends
bool UIParserActionDelegate::end(pugi::xml_node& node)
{
    return true;
}