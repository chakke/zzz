#include "CommandObserver.hpp"
#include "CommandDispatcher.hpp"
static int UNIQUE_OBSERVER_ID = 0;
CommandObserver::CommandObserver()
{
	setObserverID(UNIQUE_OBSERVER_ID++);
	setObservable(true);
}
CommandObserver::~CommandObserver(){}
std::shared_ptr<connection_object> CommandObserver::onMessage(int commandTag, std::shared_ptr<connection_object> data)
{
	return nullptr;
}
void CommandObserver::onRecieveCommand(int commandTag, std::shared_ptr<connection_object> data)
{
	if (_delegates.find(commandTag) != _delegates.end()) _delegates.at(commandTag)(data);
}

void CommandObserver::sendCommand(int tag, std::shared_ptr<connection_object> data)
{
	CommandDispatcher::getInstance()->dispatch(tag,data);
}

void CommandObserver::setObservable(bool observable)
{
	this->mObservable = observable;
}

bool CommandObserver::isObservable()
{
	return mObservable;
}

int CommandObserver::getObserverID()
{
	return mObserverID;
}

void CommandObserver::setObserverID(int id)
{
	this->mObserverID = id;
}

void CommandObserver::registerCommand(int commandTag, const std::function<void(std::shared_ptr<connection_object>)> &function)
{
	if (_delegates.find(commandTag) == _delegates.end()) _delegates.insert(std::make_pair(commandTag,function));
}

void CommandObserver::removeCommand(int commandTag)
{
	if (_delegates.find(commandTag) != _delegates.end()) {
		_delegates.erase(commandTag);
	}
}

void CommandObserver::unRegisterAllCommand()
{
	_delegates.clear();
}
