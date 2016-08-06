#pragma once
#include "AbstractDemo.hpp"

class AutoAttackDemo : public AbstractDemo {
public:
	AutoAttackDemo();
	~AutoAttackDemo();
	void onRecieveCommand(int commandTag, std::shared_ptr<connection_object> data);	
protected:
	void onGlobalTap(std::shared_ptr<connection_object> data);
	void loadEntities();
	void loadSystemAndConfig();

};
