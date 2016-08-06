#pragma once

#include "cocos2d.h"
#include "../../artemis/Component.h"

class TroopContainerComponent : public artemis::Component {

public:

	TroopContainerComponent();
	~TroopContainerComponent();
	void setTroop(int side, int type, int num);
	int getTroop(int side,int type);
	int getTotalTroop(int side);
	int getTotalTroop(int side,int type);
	void removeTroop(int side, int type,const int num = 1);
	void addTroop(int side, int type, const int num = 1);

	void removeAllTroop();
	void setCapacity(int capacity);
	int getCapacity();



protected:	
	std::map<int, std::map<int, int>> _side_troops;
	int mCapacity;
};
