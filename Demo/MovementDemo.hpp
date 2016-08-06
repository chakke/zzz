#pragma once
#include "AbstractDemo.hpp"

class MovementDemo : public AbstractDemo {
public:
	MovementDemo();
	~MovementDemo();
	void onRecieveCommand(int commandTag, std::shared_ptr<connection_object> data);	
protected:
	void onGlobalTap(std::shared_ptr<connection_object> data);
	void loadEntities();
	void loadSystemAndConfig();

};
