#include "DeviceInfo.h"
USING_NS_CC;

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

std::string DeviceInfo::getDeviceID()
{
	UIDevice *device = [UIDevice currentDevice];

	NSString  *currentDeviceId = [[device identifierForVendor]UUIDString];

	return "ios_"+std::string([currentDeviceId UTF8String]);
}

std::string DeviceInfo::getVersionCode()
{
	return "1";
}

std::string DeviceInfo::getDeviceName()
{
	NSString *deviceType = [UIDevice currentDevice].model;
	float version = [[UIDevice currentDevice].systemVersion floatValue] 

		return "Device: " + deviceType + " - iOS: " + version;
}
#elif CC_TARGET_PLATFORM == CC_PLATFORM_WP8

using namespace Windows;

std::string DeviceInfo::getDeviceID(){
	
	Platform::String^ id = Phone::System::Analytics::HostInformation::PublisherHostId;
	std::wstring fooW(id->Begin());
	std::string fooA(fooW.begin(), fooW.end());
	return fooA;
}

std::string DeviceInfo::getDeviceName(){
	return "WP8";
}

std::string DeviceInfo::getVersionCode(){
	return "1";
}

std::string DeviceInfo::getPlatform()
{
    return "WindowsPhone";
}

#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "platform/android/jni/JniHelper.h"

std::string DeviceInfo::getDeviceID()
{
    cocos2d::JniMethodInfo methodInfo;
    
    if (!cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/DeviceInfoBridge", "getDeviceId", "()Ljava/lang/String;")) {
        return "";
    }
    
    jstring object = (jstring) methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
    const char *s = methodInfo.env->GetStringUTFChars(object,NULL);
    std::string result = s;
    methodInfo.env->DeleteLocalRef(methodInfo.classID);
    methodInfo.env->DeleteLocalRef(object);
    return result;
}

std::string DeviceInfo::getDeviceName()
{
    cocos2d::JniMethodInfo methodInfo;
    
    if (!cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/DeviceInfoBridge", "getDeviceName", "()Ljava/lang/String;")) {
        return "";
    }
    
    jstring object = (jstring) methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
    const char *s = methodInfo.env->GetStringUTFChars(object,NULL);
    std::string result = s;
    methodInfo.env->DeleteLocalRef(methodInfo.classID);
    methodInfo.env->DeleteLocalRef(object);
    return result;

}

std::string DeviceInfo::getVersionCode()
{
	return "1";
}

std::string DeviceInfo::getPlatform()
{
    return "Android";
}

#else 

std::string DeviceInfo::getDeviceID()
{
	return "manh_macos3";
}

std::string DeviceInfo::getDeviceName()
{
	return "MacbookAir";
}

std::string DeviceInfo::getVersionCode()
{
	return "1";
}

std::string DeviceInfo::getPlatform()
{
    return "MacOS";
}


#endif
