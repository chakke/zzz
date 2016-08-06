
#include "PingController.hpp"
#include "../../Network/AppConnectorBuilder.hpp"
#include "../../Game/GameModel/Cache.hpp"
#include "../../Config/Config.hpp"
#include "../../Network/AppConnectorConfig.hpp"
bool PingController::init()
{    
	mTimePing = 0;
    return true;
}

void PingController::onRemove()
{
    unscheduleUpdate();
	AppConnectorBuilder::getInstance()->removeDestination(this);
	removeDestination(AppConnectorBuilder::getInstance());
}

void PingController::onLinked()
{
    scheduleUpdate();
	AppConnectorBuilder::getInstance()->addDestination(this);
	addDestination(AppConnectorBuilder::getInstance());
}

void PingController::update(float delta)
{
	if (config::__KEEP_CONNECTION_BY_PING__) {
		mTimePing += delta;
		if (mTimePing >= 120) {
			auto data = new extension_data();
			data->_cmd = cmd::__ROOM__ + "." + "ping";
			data->_object = connection_object();
			data->_sendRoom = true;
			sendData(data);
			mTimePing = 0;
		}
	}
}
