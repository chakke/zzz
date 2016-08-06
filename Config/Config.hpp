//
//  Config.hpp
//  1502
//
//  Created by Manh Tran on 1/5/16.
//
//

#ifndef Config_hpp
#define Config_hpp

#include "cocos2d.h"

namespace config
{
	extern const float  __GRAVITY__;
	extern const float  __EPSILON__;
	extern const float  __FIXED_STEP__;
	extern const bool __DEBUG_ENABLE__;
	extern const bool __DEBUG_REQUEST__;
	extern const bool __DEBUG_RESPONSE__;
	extern const bool __DEBUG_RESPONSE_POSITION__;
	extern const bool __SMARTFOX_ENABLE__;
	extern const bool __TEST_UI_PARSER__;	
	extern const bool __TEST_DEMO__;

	extern bool __DEBUG_FIXED_POSITION__;
	extern int __CACHED_STEP__;
	extern int __DELAY_SYNCHRONIZE_TIME__;
	extern int __SERVER_STEP__;
	extern bool __USE_SPEED_UP__;
	extern bool __USE_ONLINE_SERVER__;
	extern bool __SHAKE_SCREEN_ENABLE__;
	extern int __LAG_TIME_ACCEPTED__;
	extern int __UDP_STATE__;
	extern bool __KEEP_CONNECTION_BY_PING__;
	extern bool __ENABLE_LAG_TIME_MONITOR__;
};

#endif /* Config_hpp */
