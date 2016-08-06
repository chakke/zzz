#pragma once
#include "cocos2d.h"
class Grid : public cocos2d::Ref {


public:	
	enum class Type {
		 DYNAMIC,STATIC
	};
	Grid(int x, int y, float value, Grid::Type type = Grid::Type::DYNAMIC);
	virtual void setType(Grid::Type type);
	virtual Grid::Type getType();
	virtual void setGrid(int x, int y);
	virtual void setValue(float value);
	virtual float getValue();
	virtual int getX();
	virtual int getY();
	virtual bool hasEntities();
	virtual void removeAllEntities();
	virtual std::vector<int> getEntities();
	virtual void addEntity(int id);
protected:
	int x;
	int y;
	float value;
	Grid::Type type;
	std::vector<int> _entities;
};


