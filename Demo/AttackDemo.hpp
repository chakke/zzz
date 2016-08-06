#pragma once

#include "AbstractDemo.hpp"

class AttackDemo : public AbstractDemo {
public:
	AttackDemo();
	~AttackDemo();
	void onRecieveCommand(int commandTag, std::shared_ptr<connection_object> data);	
protected:
	void onGlobalTap(std::shared_ptr<connection_object> data);
	void loadEntities();
	void loadSystemAndConfig();

};
