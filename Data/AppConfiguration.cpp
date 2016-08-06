//
//  AppConfiguration.cpp
//  GameBai69
//
//  Created by Manh Tran on 2/20/16.
//
//

#include "AppConfiguration.hpp"
#include "../Config/Config.hpp"
#include "../Data/AppString.hpp"
namespace app_configuration
{
	void setupServer() {
		if (config::__USE_ONLINE_SERVER__) {
			__HOST__ = "125.212.192.94";
			__SOCKET_PORT_TCP__ = 9941;
			__SOCKET_PORT_UDP__ = 9942;
			__ZONE_GAME__ = "ArcadeDotaZone";
		}
		else {
			__HOST__ = "192.168.1.246";
			__SOCKET_PORT_TCP__ = 9933;
			__SOCKET_PORT_UDP__ = 9934;
			__ZONE_GAME__ = "ArcadeDotaZone";	
		}
	}

	void setup()
    {
        __TITLE__ = app_string::getValueMap("strings/strings.plist")->at("TITLE").asString();       
        __GET_CONFIG_HTTP__ = false;

		setupServer();
    }

    std::string __TITLE__ = "";
    std::string __VERSION_CODE__ = "15/12/2015";
    std::string __VERSION_NAME__ = "1.1.0";
    std::string __PACKAGE_NAME__ = "com.gamebai.bai69vip";
    std::string __HOT_LINE__ = "";
    std::string __LOBBY_ROOM__ = "The Lobby";
    
    std::string __HOST_SUB__ = "203.113.159.204";
    std::string __UPLOAD_URI__ = "http://203.113.159.204/Bai69FileUpload/ProfilePicture";
    std::string __UPLOAD_HOST_2__ = "203.113.159.204";
    std::string __UPLOAD_PATH_2__ = "Bai69FileUpload/ProfilePicture";
    int __SOCKET_PORT_UDP__ = 9934;
    std::string __PREFERENCE_NAME__ = "bai69";
    
    std::string __HOST__ = "server.bai69.com";
    int __SOCKET_PORT_TCP__ = 9933;
    std::string __ZONE_GAME__ = "BombOnlineZone";
    
    bool __GET_CONFIG_HTTP__ = true;
    bool __DEBUG__ = false;
    bool __USE_PAYMENT__ = false;
    
    std::vector<int> __LIST_ACTIVE_ID_GAME_CLIENT__ = {0, 2, 3, 4, 5, 6, 7, 8, 10, 11, 12};
    int __WEB_PORT__ = 8888;
    bool __USE_PING_PONG__ = false;
    bool __USE_UDP__ = false;
    bool __USE_FACEBOOK_LOGIN__ = true;
    bool __USE_SMS__ = true;
    bool __USE_FREE_COIN__ = false;
    bool __USE_TRANSFER_COIN__ = false;
    bool __SOUND__ = true;
    bool __VIBRATE__ = false;
    bool __NOTIFICATION__ = true;
    bool __VERIFY_APPSTORE__ = false;
    
    long __PARTNER_ID__ = 1;
    std::string __REF_CODE__ = "0";
    bool __USE_REFCODE__ = false;
    
    std::string __CONFIG_URL__ = "http://bai69.com/config/config_android_update.html";
    std::string __RULE_URL__ = "http://bai69.com/config/rules.json";
    std::string __REGULATION_URL__ = "http://bai69.com/config/regulation.json";
    std::string __REGULATION_EXCHANGE__ = "http://bai69/config/rule_doithuong.txt";
    bool __SHOW_SOCIAL_QUICKPLAY__ = true;
    bool __LAG_MONITOR__ = false;
    std::string __FAN_PAGE__ = "";
    
    bool __USE_IAP__ = true;
    bool __PAYMENT_PERMISSION__ = true;
    bool __PAYMENT_CARD__ = true;
    bool __PAYMENT_SMS__ = true;
    bool __PAYMENT_IAP__ = true;
    
    const int __APP_TYPE_ANDROID__ = 2;
    const int __APP_TYPE_IOS__ = 3;
    const int __APP_TYPE_WINDOWSPHONE__ = 5;
    const int __APP_TYPE_WEB__ = 0;
    const int __APP_TYPE_JAVA__ = 1;
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    int __APP_TYPE__ = __APP_TYPE_ANDROID__;
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    int __APP_TYPE__ = __APP_TYPE_IOS__;
#elif CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
    int __APP_TYPE__ = __APP_TYPE_JAVA__;
#elif CC_TARGET_PLATFORM == CC_PLATFORM_WP8
    int __APP_TYPE__ = __APP_TYPE_WINDOWSPHONE__;
#endif
};
