#include "Log.h"
#include "../Config/Config.hpp"


void Log::d(std::string message) {
	if (config::__DEBUG_ENABLE__) {
		CCLOG(message.c_str());
	}
}
void Log::d(std::string prefix,std::string message) {
	if (config::__DEBUG_ENABLE__) {
		CCLOG("%s : %s" ,prefix.c_str(), message.c_str());
	}
}