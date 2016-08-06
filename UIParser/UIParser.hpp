//
//  UIParser.hpp
//  1502
//
//  Created by Manh Tran on 1/8/16.
//
//

#ifndef UIParser_hpp
#define UIParser_hpp

#include "cocos2d.h"
#include "../Utils/pugixml.hpp"
#include "UIParserDelegate.hpp"
#include "UIConstraint/UIConstraintManager.hpp"
#include "CustomUI/CustomUITouchDelegate.hpp"
#include "ui/UIEditBox/UIEditBox.h"

class UIParserDelegate;

class UIParserCallback
{
public:
	virtual void begin_parse_node(pugi::xml_node& node) = 0;

	virtual void end_parse_node(pugi::xml_node& node) = 0;
};

typedef std::function<void(cocos2d::ui::EditBox*)> ParserEditBoxDelegate;
typedef std::function<void(cocos2d::ui::EditBox*, const std::string&)> ParserEditBoxTextChangedDelegate;

class UIParser : public cocos2d::Ref, public pugi::xml_tree_walker, public Observable, public cocos2d::ui::EditBoxDelegate
{
private:
    static UIParser* create();
    
    UIParser();
public:
    virtual ~UIParser();
    
    virtual bool init();
    
    static cocos2d::Node* parse(const std::string& file, UIParser* parent = nullptr, UIParserCallback* callback = nullptr);
	static cocos2d::Node* parse(const pugi::xml_node& node, UIParser* parent = nullptr, UIParserCallback* callback = nullptr);
    
    // Callback that is called when traversal begins
    virtual bool begin(pugi::xml_node& node);
    
    // Callback that is called for each node traversed
    virtual bool for_each(pugi::xml_node& node);
    
    virtual bool end_each(pugi::xml_node& node);
    
    // Callback that is called when traversal ends
    virtual bool end(pugi::xml_node& node);
    
    bool start_parse_node(pugi::xml_node& node);
    bool end_parse_node(pugi::xml_node& node);
    
    virtual void listen(Observer* sender, cocos2d::Ref* ref);
    
    virtual void editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox);
    virtual void editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox);
    virtual void editBoxReturn(cocos2d::ui::EditBox* editBox);
    virtual void editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text) ;
    
    const std::string& getCurrentFile();
    
    int _current_action;
    
    cocos2d::Map<std::string, CustomUITouchDelegate*>* getTouchDelegates();
    std::unordered_map<std::string, pugi::xml_node>* getHashXmlNodes();
    cocos2d::Map<std::string, cocos2d::Node*>* getHasNodes();
    std::vector<ParserEditBoxDelegate>* getEditBoxDelegates();
    std::vector<ParserEditBoxDelegate>* getEditBoxBeginDelegates();
    std::vector<ParserEditBoxDelegate>* getEditBoxEndDelegates();
    std::vector<ParserEditBoxTextChangedDelegate>* getEditBoxTextChangedDelegates();
private:
    std::vector<ParserEditBoxDelegate> _editBoxDelegates;
    std::vector<ParserEditBoxDelegate> _editBoxBeginDelegates;
    std::vector<ParserEditBoxDelegate> _editBoxEndDelegates;
    std::vector<ParserEditBoxTextChangedDelegate> _editBoxTextChangedDelegates;
    
    std::unordered_map<std::string, pugi::xml_node> _hashXmlNodes;
    cocos2d::Map<std::string, cocos2d::Node*> _hashNodes;
    cocos2d::Map<std::string, CustomUITouchDelegate*> _touchDelegates;
    cocos2d::Map<std::string, UIParserDelegate*> _refs;
    cocos2d::Vector<cocos2d::Node*> _stacks;
    std::vector<pugi::xml_node> _nodeStacks;
    UIConstraintManager* _constraintManager;
    std::string _current_file;
public:
    UIParser* _linked_parent;
    static cocos2d::Vector<UIConstraintManager*> __totalManagers;
	UIParserCallback* _callback;
    
    static void refreshAllViewConstraint(const int& step = 1);
};

#endif /* UIParser_hpp */
