
#include "AppConnectorBuilder.hpp"

#include "SmartFox/SmartFoxAppConnector.hpp"

AppConnector* _instance = nullptr;

AppConnector* AppConnectorBuilder::getInstance()
{
    if (!_instance)
    {
        _instance = SmartFoxAppConnector::create();
        _instance->retain();
    }
    
    return _instance;
}