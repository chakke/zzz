//
//  ObserverData.hpp
//  Busino
//
//  Created by Manh Tran on 1/19/16.
//
//

#ifndef ObserverData_hpp
#define ObserverData_hpp

#include "cocos2d.h"
#include "../Game/GameModel/User.hpp"
#include "ConnectionData.hpp"

struct network_data : public cocos2d::Ref
{
    int _id;
};

struct connect_input : public network_data
{
    connect_input() { _id = 0; }
};

struct connect_output : public network_data
{
    connect_output() { _id = 1; }
    
    std::string _result;
};

struct login_input : public network_data
{
    login_input() { _id = 2; }
    
    std::string             _username;
    std::string             _password;
    game_model::user_type   _type;
    long                    _partner_id;
    std::string             _ref_code;
    std::string             _imei;
    std::string             _version_code;
};

struct login_output : public network_data
{
    login_output() { _id = 3; }
    
    std::string _result;
    std::string _message;
    
    connection_object _object;
    
    std::string _guest_acount;
};

struct log_out_input : public network_data
{
    log_out_input() { _id = 4; }
};

struct log_out_output : public network_data
{
    log_out_output() { _id = 5; }
};

struct ping_pong_input : public network_data
{
	ping_pong_input() { _id = 44; _enable = true; _time = 4; _packs = 30; }
	bool _enable;
	float _time;
	int _packs;
};

struct ping_pong_output : public network_data
{
	ping_pong_output() { _id = 45; _lag_time = 0; }

	int _lag_time;
};

struct join_room_input : public network_data
{
    join_room_input() { _id = 6; }
    
    std::string _room_name;
    std::string _password;
};

struct join_room_output : public network_data
{
    join_room_output() { _id = 7; }
    
    std::string _notity_room_name;
};
struct leave_room_input : public network_data
{
	leave_room_input() { _id = 8; }
	std::string _room_name;
};

struct leave_room_output : public network_data
{
	leave_room_output() { _id = 9; }

	std::string _room_name;
};

struct disconnect_input : public network_data
{
    disconnect_input() { _id = 13; }
};

struct extension_data : public network_data
{
    extension_data()
    {
        _id = 14;
        _sendRoom = false;
    }
    
    connection_object _object;
    std::string _cmd;
    bool _sendRoom;
};

#endif /* ObserverData_hpp */
