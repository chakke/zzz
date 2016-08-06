#include "CommandDispatcher.hpp"

CommandDispatcher* dispatcher = nullptr;
CommandDispatcher::CommandDispatcher() {}
CommandDispatcher * CommandDispatcher::getInstance()
{	
	if (!dispatcher) dispatcher = new CommandDispatcher();
	return dispatcher;
}

std::shared_ptr<connection_object> CommandDispatcher::dispatchForResult(int command, std::shared_ptr<connection_object> data)
{
	for (auto x : _listeners) {
		auto observer = x.second;
		if (observer->isObservable()) {
			auto dt = observer->onMessage(command, data);
			if (dt) return dt;
		}
	}
	return nullptr;
}



void CommandDispatcher::dispatch(int commandTag, std::shared_ptr<connection_object> data)
{
	for (auto x : _listeners) {
		auto observer = x.second;
		if (observer->isObservable()) {
			observer->onRecieveCommand(commandTag, data);
		}
	}
}

void CommandDispatcher::dispatch(int observerID, int commandTag, std::shared_ptr<connection_object> data)
{
	for (auto x : _listeners) {
		auto id = x.first;
		if (id == observerID) {
			auto observer = x.second;
			if (observer->isObservable()) {
				observer->onRecieveCommand(commandTag, data);
			}
		}
	}
}

void CommandDispatcher::registerObserver(CommandObserver * observer)
{
	if (observer) {
		if (_listeners.find(observer->getObserverID()) == _listeners.end()) {
			_listeners.insert(std::make_pair(observer->getObserverID(), observer));
		}
		else {
			CCLOG("Oberser with id : %d already added", observer->getObserverID());
		}
	}

}

void CommandDispatcher::unRegisterObserver(int observerID)
{
	if (_listeners.find(observerID) != _listeners.end()) {
		_listeners.erase(observerID);
	}
}

void CommandDispatcher::unRegisterAll()
{
	_listeners.clear();
}
