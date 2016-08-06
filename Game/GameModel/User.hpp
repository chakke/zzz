
#ifndef User_hpp
#define User_hpp

#include "cocos2d.h"
#include "GameType.hpp"
#include "Room.hpp"
namespace game_model
{
	typedef long long user_id;
	typedef int user_type;
	typedef long long user_money;

	extern user_type __USER__;
	extern user_type __FACEBOOK__;
	extern user_type __QUICK__;

	struct User
	{
		user_id					_id;
		std::string				_account;
		std::string				_password;
		user_type				_type;
		std::string				_name;
		std::string				_user_id;
		std::string				_phone;
		bool					_vip;
		bool					_remember_password;
		user_money				_money;
		std::string				_avatar_url;
		std::string				_joined_room_name;
		int				_joined_room_id;
	};
};

#endif /* User_hpp */
