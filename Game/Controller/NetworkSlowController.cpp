
#include "NetworkSlowController.hpp"
#include "../../UIParser/Atlas/AtlasCache.hpp"
#include "../../UIParser/CustomUI/CustomUIData.h"
#include "../../Network/AppConnectorConfig.hpp"
#include "../../Data/ObserverData.hpp"
#include "../../Network/AppConnectorBuilder.hpp"
#include "../../UIParser/CustomUI/CustomUIRichText.h"
bool NetworkSlowController::init()
{
	auto node = UIParser::parse("xml/low_network.xml");
	setView(node);
	mRootParser = (UIParser*)dynamic_cast<CustomUIData*>(node)->getCustomUIData().at(0);

	_cmd_delegates.insert(std::make_pair(cmd::__UPDATE_STATE__, CC_CALLBACK_1(NetworkSlowController::onUpdateStates, this)));
	_cmd_delegates.insert(std::make_pair(cmd::__FINISH_MATCH__, CC_CALLBACK_1(NetworkSlowController::onFinishMatch, this)));
	_cmd_delegates.insert(std::make_pair(cmd::__NEW_MATCH__, CC_CALLBACK_1(NetworkSlowController::onNewMatch, this)));
	_cmd_delegates.insert(std::make_pair(cmd::__RESET_MATCH__, CC_CALLBACK_1(NetworkSlowController::onResetMatch, this)));

	mCountResponse = 0;
	return true;
}

void NetworkSlowController::onRemove()
{
	unscheduleUpdate();
	AppConnectorBuilder::getInstance()->removeDestination(this);
	removeDestination(AppConnectorBuilder::getInstance());
}

void NetworkSlowController::onLinked()
{
	scheduleUpdate();
	AppConnectorBuilder::getInstance()->addDestination(this);
	addDestination(AppConnectorBuilder::getInstance());
}

void NetworkSlowController::update(float delta)
{

}

void NetworkSlowController::showNetworkSlow(bool networkSlow)
{
	if (getView()) {
		getView()->setVisible(networkSlow);
	}
}

void NetworkSlowController::listen(Observer * sender, cocos2d::Ref * ref)
{
	auto data = dynamic_cast<extension_data*>(ref);
	if (data) {
		const auto& it = _cmd_delegates.find(data->_cmd);
		if (it != _cmd_delegates.end())
		{
			it->second(data->_object);
		}
	}
}


void NetworkSlowController::updateTextLoading()
{
	
}

void NetworkSlowController::onUpdateStates(connection_object object)
{
	
}

void NetworkSlowController::onFinishMatch(connection_object object)
{
	showNetworkSlow(false);
}

void NetworkSlowController::onNewMatch(connection_object object)
{
	mCountResponse = 0;
}

void NetworkSlowController::onResetMatch(connection_object object)
{
	showNetworkSlow(false);
}
