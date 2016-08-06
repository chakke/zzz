
#ifndef AppConfiguration_hpp
#define AppConfiguration_hpp

#include "cocos2d.h"

namespace app_configuration
{
	void setupServer();
	void setup();
    
    extern std::string __TITLE__;
    extern std::string __VERSION_CODE__;
    extern std::string __VERSION_NAME__;
    extern std::string __PACKAGE_NAME__;
    extern std::string __HOT_LINE__;
    extern std::string __HOST_SUB__;
    extern std::string __UPLOAD_URI__;
    extern std::string __UPLOAD_HOST_2__;
    extern std::string __UPLOAD_PATH_2__;
    extern int __SOCKET_PORT_UDP__;
    extern std::string __PREFERENCE_NAME__;
    extern std::string __LOBBY_ROOM__;
    
    extern std::string __HOST__;
    extern int __SOCKET_PORT_TCP__;
    extern std::string __ZONE_GAME__;
    extern bool __GET_CONFIG_HTTP__;
    extern bool __DEBUG__;
    extern bool __USE_PAYMENT__;
    
    extern std::vector<int> __LIST_ACTIVE_ID_GAME_CLIENT__;
    extern int __WEB_PORT__;
    extern bool __USE_PING_PONG__;
    extern bool __USE_UDP__;
    extern bool __USE_FACEBOOK_LOGIN__;
    extern bool __USE_SMS__;
    extern bool __USE_FREE_COIN__;
    extern bool __USE_TRANSFER_COIN__;
    extern bool __SOUND__;
    extern bool __VIBRATE__;
    extern bool __NOTIFICATION__;
    extern bool __VERIFY_APPSTORE__;
    
    extern long __PARTNER_ID__;
    extern std::string __REF_CODE__;
    extern bool __USE_REFCODE__;
    
    extern std::string __CONFIG_URL__;
    extern std::string __RULE_URL__;
    extern std::string __REGULATION_URL__;
    extern std::string __REGULATION_EXCHANGE__;
    extern bool __SHOW_SOCIAL_QUICKPLAY__;
    extern bool __LAG_MONITOR__;
    extern std::string __FAN_PAGE__;
    
    extern const int __APP_TYPE_ANDROID__;
    extern const int __APP_TYPE_IOS__;
    extern const int __APP_TYPE_WINDOWSPHONE__;
    extern const int __APP_TYPE_WEB__;
    extern const int __APP_TYPE_JAVA__;
    extern int __APP_TYPE__;
    
    extern bool __USE_IAP__;
    extern bool __PAYMENT_PERMISSION__;
    extern bool __PAYMENT_CARD__;
    extern bool __PAYMENT_SMS__;
    extern bool __PAYMENT_IAP__;
};

#endif /* AppConfiguration_hpp */
