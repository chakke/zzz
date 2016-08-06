#pragma once

#include "../../AppController/Controller.hpp"
#include "../GameModel/Room.hpp"
#include "../GameModel/GameType.hpp"
#include "../../Data/ObserverData.hpp"

class ChoiceRoomController : public Controller
{
public:
	CREATE_FUNC(ChoiceRoomController);

    virtual bool init();
    
    virtual void onRemove();
    
    virtual void onLinked();
    
    virtual void update(float delta);
    
    virtual void listen(Observer* sender, cocos2d::Ref* ref);
    
    void refresh(std::vector<std::shared_ptr<game_model::Room>> tables);
    
    std::string _joining_room;
    std::shared_ptr<game_model::Room> _joined_table;	
    void load();

};


