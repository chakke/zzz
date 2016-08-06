#include "ChoiceRoomController.hpp"
#include "../../UIParser/UIParser.hpp"
#include "../../UIParser/CustomUI/CustomUIData.h"
#include "../../UIParser/CustomUI/CustomUIImageView.hpp"
#include "../../UIParser/CustomUI/CustomUIRichText.h"
#include "../../UIParser/CustomUI/CustomUIListView.hpp"
#include "../../UIParser/Atlas/AtlasCache.hpp"
#include "../../Utils/Functions.hpp"
#include "../../Network/AppConnectorBuilder.hpp"

#include "../GameModel/GameType.hpp"
#include "../../Network/AppConnectorConfig.hpp"
#include "LoginController.hpp"
#include "ConnectionController.hpp"
#include "../GameModel/Cache.hpp"
namespace choice_room_controller
{
    struct choice_room_table_info : public cocos2d::Ref
    {
        std::shared_ptr<game_model::Room> _table;
    };
	
    void on_touch_back(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type, ChoiceRoomController* controller)
    {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
        {
			ConnectionController::getInstance()->disconnect(false);

			auto loginController = LoginController::create();
            auto parent = controller->getParent();
            parent->addSubController(loginController);
            parent->getView()->addChild(loginController->getView());
			loginController->update(0);
			
            
            app_function::destroyTree(controller->getView());
            controller->getView()->removeFromParent();
            controller->removeSelf(true);

			
        }
    }
    
    void on_ask_password_ok(const std::string& password, choice_room_table_info* info, ChoiceRoomController* controller)
    {
        controller->_joined_table = std::shared_ptr<game_model::Room>(info->_table);
        controller->_joining_room = info->_table->_room_name;
		
        auto input = new join_room_input();
        input->_room_name = info->_table->_room_name;
        input->_password = password;
        controller->sendData(input);
		CCLOG("Send Data join room output");
    }
    
    void on_touch_item(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type, ChoiceRoomController* controller)
    {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
        {
			CCLOG("Touch to item .....");
            auto node = dynamic_cast<cocos2d::Node*>(sender);
            choice_room_table_info* info = dynamic_cast<choice_room_table_info*>(node->getUserObject());
         
			{
				on_ask_password_ok("", info, controller);
			}
        }
    }
    
    void changeTop(UIParser* parser, const std::string& top, const std::string& bottom, const std::string& icon)
    {
        auto uplabel = dynamic_cast<CustomRichText*>(parser->getHasNodes()->at("up"));
        uplabel->getRichElement<CustomRichElementText*>(0)->_text = top;
        uplabel->updateText();
        
        auto bottomlabel = dynamic_cast<CustomRichText*>(parser->getHasNodes()->at("bottom"));
        bottomlabel->getRichElement<CustomRichElementText*>(0)->_text = bottom;
        bottomlabel->updateText();
    }
};

bool ChoiceRoomController::init()
{

    auto node = UIParser::parse("xml/choiceroom.xml");
    setView(node);
    auto parser = (UIParser*)dynamic_cast<CustomUIData*>(node)->getCustomUIData().at(0);
    parser->getTouchDelegates()->at("touchback")->setDelegate(std::bind(choice_room_controller::on_touch_back, std::placeholders::_1, std::placeholders::_2, this));
	parser->getTouchDelegates()->at("touch_item")->setDelegate(std::bind(choice_room_controller::on_touch_item, std::placeholders::_1, std::placeholders::_2, this));

	auto userName = dynamic_cast<CustomRichText*>(parser->getHasNodes()->at("username"));	
	userName->getRichElement<CustomRichElementText*>(0)->_text = game_model::__user_cache__->_account.c_str();
	userName->updateText();

	
	auto listview = dynamic_cast<CustomUIListView*> (parser->getHasNodes()->at("listview"));
	listview->setBounceEnabled(false);


    return true;
}

void ChoiceRoomController::onRemove()
{
    AppConnectorBuilder::getInstance()->removeDestination(this);
    removeDestination(AppConnectorBuilder::getInstance());
}

void ChoiceRoomController::onLinked()
{
    AppConnectorBuilder::getInstance()->addDestination(this);
    addDestination(AppConnectorBuilder::getInstance());
    
    load();	
}

void ChoiceRoomController::load()
{
	
	auto data = new extension_data();
    data->_cmd = cmd::__ZONE__ + "." + cmd::__GET_LIST_ROOM__;
	data->_sendRoom = false;
    sendData(data);
}

//void ChoiceRoomController::onQuickPlayClick(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
//{
//	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
//		auto parser = (UIParser*)dynamic_cast<CustomUIData*>(_view)->getCustomUIData().at(0);
//		auto table = parser->getHasNodes()->at("table");
//
//		auto tableparser = (UIParser*)dynamic_cast<CustomUIData*>(table)->getCustomUIData().at(0);
//		auto listitem = tableparser->getHasNodes()->at("itemlist");
//
//		for (auto child : listitem->getChildren()) {
//			//auto data = dynamic_cast<choice_room_controller::choice_room_table_info*>(child->getUserObject());
//			//if (data->_table->_current_players % 2 == 1) {
//			////	choice_room_controller::on_touch_item(child, type, this);
//			//	return;
//			//}
//		}
//	}
//}

void ChoiceRoomController::update(float delta)
{
    
}

void ChoiceRoomController::listen(Observer* sender, cocos2d::Ref* ref)
{
    
    {
        auto data = dynamic_cast<extension_data*>(ref);
        if(data && data->_cmd.compare(cmd::__GET_LIST_ROOM__) == 0)
        {
            std::vector<std::shared_ptr<game_model::Room>> _tables;
            //
            std::shared_ptr<connection_array> rooms = data->_object.getArray(extparamskey::__LIST_ROOM__);
            for (long i = 0; i < rooms->Size(); i++)
            {
                std::shared_ptr<connection_object> object = rooms->getObject(i);
                std::shared_ptr<game_model::Room> table = std::shared_ptr<game_model::Room>(new game_model::Room());
            
                if (object->containsKey(extparamskey::__MAX_PLAYER__)) {
                    table->_max_player = object->getInt(extparamskey::__MAX_PLAYER__);
                }
				if (object->containsKey(extparamskey::__CURRENT_PLAYER__)) {
					table->_current_players = object->getInt(extparamskey::__CURRENT_PLAYER__);
				}

				if (object->containsKey(extparamskey::__ROOM_ID__)) {
					table->_room_id = object->getInt(extparamskey::__ROOM_ID__);
				}
				if (object->containsKey(extparamskey::__ROOM_NAME__)) {
					table->_room_name = *object->getString(extparamskey::__ROOM_NAME__);
				}                
                _tables.push_back(std::shared_ptr<game_model::Room>(table));
            }
            
            refresh(_tables);
        }
    }
}

void ChoiceRoomController::refresh(std::vector<std::shared_ptr<game_model::Room>> tables)
{
    auto parser = (UIParser*)dynamic_cast<CustomUIData*>(_view)->getCustomUIData().at(0);
 
    auto listitem = dynamic_cast<CustomUIListView*> (parser->getHasNodes()->at("listview"));
    listitem->removeAllChildren();
    auto xmlnode = parser->getHashXmlNodes()->at("rooms");
    for (int i = 0; i < tables.size(); i+=5)
    {        
        auto item = UIParser::parse(xmlnode, parser);
        auto itemparser = (UIParser*)dynamic_cast<CustomUIData*>(item)->getCustomUIData().at(0);
		listitem->addChild(item);
		int index = 0;
		while (index < 5) {			

			
			auto room = itemparser->getHasNodes()->at(cocos2d::StringUtils::format("room_%d",index+1).c_str());
			if ((i + index) < tables.size()) {
				room->setVisible(true);
				auto roomParser = (UIParser*)dynamic_cast<CustomUIData*>(room)->getCustomUIData().at(0);


				std::shared_ptr<game_model::Room> tables_i = tables.at(tables.size() - i - index - 1);
				choice_room_controller::choice_room_table_info* info = new choice_room_controller::choice_room_table_info();
				info->autorelease();
				info->_table = std::shared_ptr<game_model::Room>(tables_i);
				room->setUserObject(info);

				auto roomTexture = dynamic_cast<CustomUIImageView*>(roomParser->getHasNodes()->at("room_texture"));
				roomTexture->setSpriteFrame(atlas_cache::getSpriteFrame("atlas/choice_room.plist", tables_i->_current_players>0 ? "room.png" : "room2.png"));

				auto idlabel = dynamic_cast<CustomRichText*>(roomParser->getHasNodes()->at("room_id"));
				idlabel->getRichElement<CustomRichElementText*>(0)->_text = cocos2d::StringUtils::format("P. %d", tables_i->_room_id);
				idlabel->updateText();
				idlabel->setCascadeOpacityEnabled(true);

				auto titlelabel = dynamic_cast<CustomRichText*>(roomParser->getHasNodes()->at("room_name"));
				titlelabel->getRichElement<CustomRichElementText*>(0)->_text = tables_i->_room_name;
				titlelabel->updateText();
				titlelabel->setCascadeOpacityEnabled(true);

				auto capacity = dynamic_cast<CustomRichText*>(roomParser->getHasNodes()->at("room_capacity"));
				capacity->getRichElement<CustomRichElementText*>(0)->_text = cocos2d::StringUtils::format("%d/%d", tables_i->_current_players, tables_i->_max_player);
				capacity->updateText();
				capacity->setCascadeOpacityEnabled(true);

				for (int idx = 0; idx < 4; idx++) {
					auto img = dynamic_cast<CustomUIImageView*>(roomParser->getHasNodes()->at(cocos2d::StringUtils::format("player_%d", idx + 1).c_str()));
					img->setSpriteFrame(atlas_cache::getSpriteFrame("atlas/choice_room.plist", (idx < tables_i->_current_players) ? "user_on.png" : "user_off.png"));
					img->setCascadeOpacityEnabled(true);
				}
			}
			else {
				room->setVisible(false);
			}
			index++;
		}



	
		



		/*auto idlabel = dynamic_cast<CustomRichText*>(itemparser->getHasNodes()->at("room_id"));
		idlabel->getRichElement<CustomRichElementText*>(0)->_text = cocos2d::StringUtils::format("%d", tables_i->_room_id);
		idlabel->updateText();
		idlabel->setCascadeOpacityEnabled(true);

        auto titlelabel = dynamic_cast<CustomRichText*>(itemparser->getHasNodes()->at("room_name"));
        titlelabel->getRichElement<CustomRichElementText*>(0)->_text = tables_i->_room_name;
        titlelabel->updateText();
		titlelabel->setCascadeOpacityEnabled(true);

		auto capacity = dynamic_cast<CustomRichText*>(itemparser->getHasNodes()->at("room_capacity"));
		capacity->getRichElement<CustomRichElementText*>(0)->_text = cocos2d::StringUtils::format("%d/%d", tables_i->_current_players, tables_i->_max_player);
		capacity->updateText();
		capacity->setCascadeOpacityEnabled(true);

		for (int i = 0; i < 4; i++) {
			auto img = dynamic_cast<CustomUIImageView*>(itemparser->getHasNodes()->at(cocos2d::StringUtils::format("player_%d", i).c_str()));
			img->setSpriteFrame(atlas_cache::getSpriteFrame("atlas/choice_room.plist", (i < tables_i->_current_players) ? "user_on.png" : "user_off.png" ));
			img->setCascadeOpacityEnabled(true);			
		}*/

    
		/*item->setVisible(false);		
		item->setCascadeOpacityEnabled(true);

		for (auto c : item->getChildren()) {
			c->setCascadeOpacityEnabled(true);
		}

		item->runAction(cocos2d::Sequence::create(cocos2d::FadeOut::create(0), cocos2d::CallFunc::create([=]() {
			item->setVisible(true);
		}),cocos2d::DelayTime::create(.1f+i*.05f),cocos2d::FadeIn::create(.1f), nullptr));*/

		listitem->scrollToBottom(1.5f,true);
		UIParser::refreshAllViewConstraint(2);
    }
}
