#include "AppConnector.hpp"

USING_NS_CC;

AppConnector::~AppConnector()
{
    _apiDelegates.clear();
    _refMap.clear();
}