#pragma once

#include "cocos2d.h"
#include "../../artemis/Component.h"
#include "../../Data/ConnectionData.hpp"

namespace actioncomponent{
	struct Action {
		bool done;
		int name;
		float time;
		std::shared_ptr<connection_object> data;
		Action(int name,float time, std::shared_ptr<connection_object> data) : name(name),data(data),done(false),time(time){};
		bool update(float delta) { 
			this->time = MAX(this->time - delta, 0);
			if (this->time == 0) {
				this->done = true;
				return true;
			}
			return false;
		}
	};
}

class ActionComponent : public artemis::Component {

public:
	ActionComponent();
	~ActionComponent();

	void addAction(int name,float delay = 0, std::shared_ptr<connection_object> data = nullptr);
	void setAction(int name,float delay = 0, std::shared_ptr<connection_object> data = nullptr);
	void removeAction(int name);
	std::vector<actioncomponent::Action> getActions();
	actioncomponent::Action getRunningAction();	
	actioncomponent::Action pop();
	actioncomponent::Action peek();	
	void removeAllActions();
protected:
	std::vector<actioncomponent::Action>  _actions;
};
