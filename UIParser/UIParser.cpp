//
//  UIParser.cpp
//  1502
//
//  Created by Manh Tran on 1/8/16.
//
//

#include "UIParser.hpp"
#include "UIParser_IMG_Delegate.hpp"
#include "UIParser_Layout_Delegate.hpp"
#include "UIParser_Label_Delegate.hpp"
#include "UIParser_LabelBMF_Delegate.hpp"
#include "UIParser_Text_Delegate.hpp"
#include "UIParser_Button_Delegate.hpp"
#include "UIParser_ListView_Delegate.hpp"
#include "UIParser_Action_Delegate.hpp"
#include "UIParser_TouchDelegate_Delegate.hpp"
#include "UIParser_TextField_Delegate.hpp"
#include "UIParser_Change_Texture_Delegate.hpp"
#include "UIParser_PageView_Delegate.hpp"
#include "ui/UILayout.h"
#include "CustomUI/CustomUIData.h"
#include "CustomUI/CustomUIInterface.hpp"

USING_NS_CC;

cocos2d::Vector<UIConstraintManager*> UIParser::__totalManagers;

namespace ui_parser_custom
{
    class ui_parser_manager_update
    {
    public:
        
        void update(float delta)
        {
            for (int i = 0; i < UIParser::__totalManagers.size(); i++)
            {
                UIConstraintManager* manager = UIParser::__totalManagers.at(i);
                if (manager->getReferenceCount() > 1)
                {
                    manager->custom_update(delta);
                }
                else
                {
                    UIParser::__totalManagers.erase(i);
                    i--;
                }
            }
        }
    };
    
    ui_parser_manager_update* _instance_manager_update = nullptr;
};

void UIParser::refreshAllViewConstraint(const int& step)
{
    if (ui_parser_custom::_instance_manager_update && Director::getInstance()->getRunningScene())
    {
        for (int i = 0; i < step; i++)
        {
            //Director::getInstance()->getRunningScene()->render(Director::getInstance()->getRenderer());
            ui_parser_custom::_instance_manager_update->update(0);
            //Director::getInstance()->getRenderer()->clean();
			//cocos2d::Director::getInstance()->mainLoop();
        }
    }
}

UIParser* UIParser::create()
{
    auto ret = new UIParser();
    ret->init();
    ret->autorelease();
    return ret;
}

UIParser::UIParser() : _constraintManager(nullptr), _current_action(0), _linked_parent(nullptr), _callback(nullptr)
{
    
}

UIParser::~UIParser()
{
    _refs.clear();
    _stacks.clear();
    _touchDelegates.clear();
    _nodeStacks.clear();
    _hashNodes.clear();
    _hashXmlNodes.clear();
}

bool UIParser::init()
{
    if ( ! ui_parser_custom::_instance_manager_update)
    {
        ui_parser_custom::_instance_manager_update = new ui_parser_custom::ui_parser_manager_update();
        Director::getInstance()->getScheduler()->scheduleUpdate(ui_parser_custom::_instance_manager_update, 0, false);
    }
    
    _refs.insert("img", UIParserImgDelegate::create(this));
    _refs.insert("layout", UIParserLayoutDelegate::create(this));
    _refs.insert("label", UIParserLabelDelegate::create(this));
	_refs.insert("labelBMF", UIParserLabelBMFDelegate::create(this));
    _refs.insert("button", UIParserButtonDelegate::create(this));
    _refs.insert("group", UIParserButtonDelegate::create(this));
    _refs.insert("listview", UIParserListViewDelegate::create(this));
    _refs.insert("pageview", UIParserPageViewDelegate::create(this));
    _refs.insert("", UIParserTextDelegate::create(this));
    _refs.insert("action", UIParserActionDelegate::create(this));
    _refs.insert("touchdelegate", UIParserTouchDelegateDelegate::create(this));
    _refs.insert("textfield", UIParserTextFieldDelegate::create(this));
    _refs.insert("changetexture", UIParserChangeTextureDelegate::create(this));
    return true;
}

const std::string& UIParser::getCurrentFile()
{
    return _current_file;
}

cocos2d::Map<std::string, CustomUITouchDelegate*>* UIParser::getTouchDelegates()
{
    return &_touchDelegates;
}

std::unordered_map<std::string, pugi::xml_node>* UIParser::getHashXmlNodes()
{
    return &_hashXmlNodes;
}

cocos2d::Map<std::string, cocos2d::Node*>* UIParser::getHasNodes()
{
    return &_hashNodes;
}

std::vector<ParserEditBoxDelegate>* UIParser::getEditBoxDelegates()
{
    return &_editBoxDelegates;
}
std::vector<ParserEditBoxDelegate>* UIParser::getEditBoxBeginDelegates()
{
    return &_editBoxBeginDelegates;
}

std::vector<ParserEditBoxDelegate>* UIParser::getEditBoxEndDelegates()
{
    return &_editBoxEndDelegates;
}

std::vector<ParserEditBoxTextChangedDelegate>* UIParser::getEditBoxTextChangedDelegates()
{
    return &_editBoxTextChangedDelegates;
}

void UIParser::listen(Observer* sender, cocos2d::Ref* ref)
{
    auto constraint = dynamic_cast<UIConstraint*>(ref);
    if (constraint && _constraintManager)
    {
        _constraintManager->pushConstraint(constraint);
    }
}

void UIParser::editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox)
{
    for (auto it = _editBoxBeginDelegates.begin(); it != _editBoxBeginDelegates.end(); it++)
    {
        (*it)(editBox);
    }
}

void UIParser::editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox)
{
    for (auto it = _editBoxEndDelegates.begin(); it != _editBoxEndDelegates.end(); it++)
    {
        (*it)(editBox);
    }
}

void UIParser::editBoxReturn(cocos2d::ui::EditBox* editBox)
{
    for (auto it = _editBoxDelegates.begin(); it != _editBoxDelegates.end(); it++)
    {
        (*it)(editBox);
    }
}

void UIParser::editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text)
{
    for (auto it = _editBoxTextChangedDelegates.begin(); it != _editBoxTextChangedDelegates.end(); it++)
    {
        (*it)(editBox, text);
    }
}

std::unordered_map<std::string, pugi::xml_document*> _cache_doc;

cocos2d::Node* UIParser::parse(const std::string& file, UIParser* parent, UIParserCallback* callback)
{
    UIParser* parser = UIParser::create();
	parser->_callback = callback;
    parser->_linked_parent = parent;
    parser->_current_file = file;
    
    bool created_constraint = true;
    
    if(!parser->_constraintManager)
    {
        created_constraint = false;
       parser->_constraintManager = UIConstraintManager::create("constraintManager");
    }
    
    pugi::xml_document* doc = nullptr;
    
    if (_cache_doc.find(file) == _cache_doc.end()) {
        _cache_doc.insert(std::make_pair(file, new pugi::xml_document()));
        doc = _cache_doc[file];
        
        std::string fullPath = FileUtils::getInstance()->fullPathForFilename(file).c_str();
        doc->load_string(FileUtils::getInstance()->getStringFromFile(file).c_str());
    }
    else doc = _cache_doc[file];
    
    doc->traverse(*parser);
    
    while (parser->_stacks.size() > 1)
    {
        parser->_stacks.popBack();
    }
    auto ret = parser->_stacks.back();
    parser->_stacks.popBack();
    
    if(!created_constraint && !ret->getComponent("constraintManager"))
    {
        ret->addComponent(parser->_constraintManager);
        auto touchdelegatecomponent = CustomUITouchDelegateComponent::create("touchDelegates");
        touchdelegatecomponent->_delegates = parser->_touchDelegates;
        
        ret->addComponent(touchdelegatecomponent);
        ret->scheduleUpdate();
        
        __totalManagers.pushBack(parser->_constraintManager);
    }
    
    auto customuidata = dynamic_cast<CustomUIData*>(ret);
    if (customuidata)
    {
        bool attached = false;
        auto& datas = customuidata->getCustomUIData();
        for (auto d : datas) {
            if (dynamic_cast<UIParser*>(d))
            {
                attached = true;
                break;
            }
        }
        if(!attached) customuidata->addCustomUIData(parser);
    }
    
    parser->_nodeStacks.clear();
    return ret;
}

cocos2d::Node* UIParser::parse(const pugi::xml_node& node, UIParser* parent, UIParserCallback* callback)
{
    UIParser* parser = UIParser::create();
    parser->_linked_parent = parent;
	parser->_callback = callback;
    
    bool created_constraint = true;
    
    if(!parser->_constraintManager)
    {
        created_constraint = false;
        parser->_constraintManager = UIConstraintManager::create("constraintManager");
    }
    
    pugi::xml_node n = node;
    n.traverse(*parser, 0);
    while (parser->_stacks.size() > 1)
    {
        parser->_stacks.popBack();
    }
    auto ret = parser->_stacks.back();
    parser->_stacks.popBack();
    
    if(!created_constraint && !ret->getComponent("constraintManager"))
    {
        ret->addComponent(parser->_constraintManager);
        auto touchdelegatecomponent = CustomUITouchDelegateComponent::create("touchDelegates");
        touchdelegatecomponent->_delegates = parser->_touchDelegates;
        
        ret->addComponent(touchdelegatecomponent);
        ret->scheduleUpdate();
        
        __totalManagers.pushBack(parser->_constraintManager);
    }
    
    auto customuidata = dynamic_cast<CustomUIData*>(ret);
    if (customuidata)
    {
        bool attached = false;
        auto& datas = customuidata->getCustomUIData();
        for (auto d : datas) {
            if (dynamic_cast<UIParser*>(d))
            {
                attached = true;
                break;
            }
        }
        if(!attached) customuidata->addCustomUIData(parser);
    }
    
    parser->_nodeStacks.clear();
    return ret;
}

// Callback that is called when traversal begins
bool UIParser::begin(pugi::xml_node& node)
{
	if (_callback) _callback->begin_parse_node(node);
    return start_parse_node(node);
}

bool UIParser::for_each(pugi::xml_node& node)
{
	if (_callback) _callback->begin_parse_node(node);
    return start_parse_node(node);
}

// Callback that is called for each node traversed
bool UIParser::start_parse_node(pugi::xml_node& node)
{
    int tree_depth = this->xml_tree_walker::depth();
    long stack_depth = _stacks.size();
    long node_stack_depth = _nodeStacks.size();
    
    if (tree_depth >= node_stack_depth)
    {
        _nodeStacks.push_back(node);
    }
    else
    {
        while (tree_depth < node_stack_depth && node_stack_depth > 0)
        {
            _nodeStacks.pop_back();
            node_stack_depth = _nodeStacks.size();
        }
        _nodeStacks.push_back(node);
    }
    pugi::xml_node prev_node;
    if (_nodeStacks.size() > 1)
    {
        prev_node = _nodeStacks.at(_nodeStacks.size() - 2);
    }
    
    Node* ret = nullptr;
    auto callback = _refs.at(node.name());
    if (callback)
    {
        ret = callback->createNode(node);
    }
    
    if (tree_depth == stack_depth)
    {
        if (stack_depth > 0)
        {
            Node* parent = _stacks.back();
            if(ret)
            {
                auto customIn = dynamic_cast<CustomUIInterface*>(parent);
                if (customIn)
                {
                    customIn->attach_node(ret);
                }
                else parent->addChild(ret);
            }
            if(callback) callback->constraintWithParent(node,prev_node, parent, ret);
        }
        
        if(ret) _stacks.pushBack(ret);
    }
    else if(tree_depth > stack_depth)
    {
        if (stack_depth > 0)
        {
            Node* parent = _stacks.back();
            if(ret)
            {
                auto customIn = dynamic_cast<CustomUIInterface*>(parent);
                if (customIn)
                {
                    customIn->attach_node(ret);
                }
                else parent->addChild(ret);
            }
            if(callback) callback->constraintWithParent(node, prev_node, parent, ret);
        }
        
        if(ret) _stacks.pushBack(ret);
    }
    else
    {
        while (tree_depth < stack_depth && stack_depth > 0)
        {
            _stacks.popBack();
            stack_depth = _stacks.size();
        }
        if (stack_depth > 0)
        {
            Node* parent = _stacks.back();
            if(ret)
            {
                auto customIn = dynamic_cast<CustomUIInterface*>(parent);
                if (customIn)
                {
                    customIn->attach_node(ret);
                }
                else parent->addChild(ret);
            }
            if (callback) callback->constraintWithParent(node, prev_node, parent, ret);
        }
        
        if(ret) _stacks.pushBack(ret);
    }
    if(ret && callback) callback->processCommonConstraint(node, ret);
    return true;
}

bool UIParser::end_each(pugi::xml_node& node)
{
	if (_callback) _callback->end_parse_node(node);
    return end_parse_node(node);
}

// Callback that is called when traversal ends
bool UIParser::end(pugi::xml_node& node)
{
	if (_callback) _callback->end_parse_node(node);
    return end_parse_node(node);
}

bool UIParser::end_parse_node(pugi::xml_node& node)
{
    return true;
}