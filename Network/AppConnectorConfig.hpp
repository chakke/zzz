
#ifndef AppConnectorConfig_hpp
#define AppConnectorConfig_hpp

#include "cocos2d.h"

namespace extparamskey
{
     
	extern std::string __SUCCESS__;
    extern std::string __LIST_ROOM__;
    extern std::string __MAX_PLAYER__;
	extern std::string __CURRENT_PLAYER__;
    extern std::string __ROOM_NAME__;
	extern std::string __ROOM_ID__;
    extern std::string __LIST_PLAYERS__;
    extern std::string __STATE__;
	extern std::string __DATA__;

	extern std::string __USER_NAME__;
	extern std::string __PASSWORD__;
	extern std::string __REASON__;
	extern std::string __IS_SUCCESS__;
    
	extern std::string __ID__;
	extern std::string __NAME__;
	extern std::string __X__;
	extern std::string __Y__;

	extern std::string __WIDTH__;
	extern std::string __HEIGHT__;
	
	extern std::string __PLAYER_STATES__;
	extern std::string __TIME_STAMP__;
	
	extern std::string __SERVER_STEP__;
	extern std::string __OPTION_SPEED_UP__;
	extern std::string __SIZE_QUEUE_DELAY_INTERPOLATION__;
	extern std::string __CAN_BOMB__;
	extern std::string __PLAYER_ID__;
	extern std::string __LENGTH__;
	extern std::string __QUEUE_BOMB__;

	extern std::string __MAP__;
	extern std::string __UPDATE_MAP__;
	extern std::string __VALUE__;

	extern std::string TIME;
	extern std::string P_ID;
	extern std::string MAX_TROPS;
	extern std::string CURRENT_TROPS;
	extern std::string CURRENT_TROP;
	extern std::string NUMBER_LOCATION;
	extern std::string CAPACITY;
	extern std::string MAX_CAPACITY;
	extern std::string TIME_TRAINING_TROOP;
	extern std::string LOCATIONS;
	extern std::string LOCATION_ID;
	extern std::string LOCATION_TROPS;
	extern std::string PLAYER_TROP;
	extern std::string SOURCE ;
	extern std::string DESTINATION;
	extern std::string MATRIX;
	extern std::string NUMBER_TROP;
	extern std::string ID_LOCATION_SOURCE;
	extern std::string ID_LOCATION_DESTINATION;
	extern std::string TIME_MOVE;
};

namespace cmd
{
    extern std::string __ZONE__;
	extern std::string __ROOM__;
	extern std::string __ROOM_INFO__;
    extern std::string __REGISTER__;    
	extern std::string __GET_LIST_ROOM__;
	extern std::string __GET_USER_INFO__;
	extern std::string __NEW_PLAYER__;
	extern std::string __BUILDING__;
	extern std::string __GENERATE_TROOP__;

	extern std::string __INIT_STATE__;
	extern std::string __UPDATE_STATE__;
	extern std::string __FINISH_MATCH__;
	extern std::string __PREPARE_MATCH__;
	extern std::string __NEW_MATCH__;
	extern std::string __RESET_MATCH__;
	extern std::string __LEAVER_ROOM__;
	extern std::string __PLAYER_LEAVER__;
	extern std::string __BOMB__;
	extern std::string __FIRE_BOMB__;
	extern std::string __INIT_MAP__;
	extern std::string __MATRIX_TRANSFER__;
	extern std::string __TRANSFER_TROOP__;
	extern std::string __NOTIFY_TRANSFER_TROP__;
	extern std::string __SHOW_LOCATION_DESTINATION__;
	extern std::string __UPDATE_LOCATION__;
	
};

#endif /* AppConnectorConfig_hpp */
