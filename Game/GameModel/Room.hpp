#pragma once
#include "User.hpp"


namespace game_model
{
    struct Room
    {
		Room()
        {
			reset();            
        }
		void reset() {
			_current_players = 0;
			_max_player = 4;
			_room_id = 0;
			_room_name = "no name";
		}
        int _current_players;
        int _max_player;   
        std::string _room_name;
		int _room_id;
    };
};


