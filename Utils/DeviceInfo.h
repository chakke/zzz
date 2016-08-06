#ifndef _DEVICE_INFO_H_
#define _DEVICE_INFO_H_

#include "cocos2d.h"

    class DeviceInfo
    {
    public:
        static std::string getDeviceID();
        static std::string getDeviceName();
        static std::string getVersionCode();
        static std::string getPlatform();
    };

#endif
