//
//  Config.cpp
//  1502
//
//  Created by Manh Tran on 1/5/16.
//
//

#include "Config.hpp"

namespace config
{
    const float __GRAVITY__ = 10;
    const float __EPSILON__ = 0.1f;
    const float __FIXED_STEP__ = 0.01666666667f;	
	const bool __DEBUG_ENABLE__ = true;


	const bool __SMARTFOX_ENABLE__ = true;
	const bool __DEBUG_REQUEST__ = true;
	const bool __DEBUG_RESPONSE__ = true;
	const bool __DEBUG_RESPONSE_POSITION__ = false;
	const bool __TEST_UI_PARSER__ = false;	
	const bool __TEST_DEMO__ = true;

	bool __DEBUG_FIXED_POSITION__ = false;
	int __CACHED_STEP__ = 2;
	int __DELAY_SYNCHRONIZE_TIME__ = 150;
	int __SERVER_STEP__ = 50;
	bool __USE_SPEED_UP__ = false;
	bool __USE_ONLINE_SERVER__ = true;
	bool __SHAKE_SCREEN_ENABLE__ = false;
	int __LAG_TIME_ACCEPTED__ = 2000;
	int __UDP_STATE__ = 1;
	bool __KEEP_CONNECTION_BY_PING__ = true;
	bool __ENABLE_LAG_TIME_MONITOR__ = false;
};
