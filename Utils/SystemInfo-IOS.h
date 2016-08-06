#import <Foundation/Foundation.h>

class SystemInfo{
public:
    
    static std::string getIOSVersion();
    static std::string getDeviceType();
    static std::string getDeviceId();
    static int getNetworkType();

private:
    static std::string platformNiceString();

};