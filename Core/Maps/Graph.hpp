#pragma once
#include "cocos2d.h"
#include "Grid.hpp"
#include "../Enums.hpp"
class Graph : public cocos2d::Ref {

public:
	static Graph* create();
	static Graph* create(float width, float height, int cell_width, int cell_height, float default_value);
	static Graph* createFromFile(const std::string &xmlFile);

	void setupDefault();	
	Grid* get(int cell_x,int cell_y,game::Align align=game::Align::CENTER);
	Grid* get(float x, float y, game::Align align = game::Align::CENTER);

	bool isInMap(float x, float y);
	bool isInMap(int x, int y);

	int getCellWidth();
	int getCellHeight();

	int getWorldWidth();
	int  getWorldHeight();
	
	void setDefaultValue(float value);
	void setWorldWidth(int world_width);
	void setWorldHeight(int world_height);
	void setCellWidth(int cell_width);
	void setCellHeight(int cell_height);

	void setName(std::string name);
	std::string getName();

	

	void debug(cocos2d::DrawNode* drawnode);
	void console();
	void removeDynamicEntities();
	void addDynamicEntity(cocos2d::Vec2 position, int id,bool fillNeighbors = false);
	void addDynamicEntity(int cx, int cy, int id, bool fillNeighbors = false);

	void fillRange(cocos2d::Vec2 position, float rw, float rh, int value);
protected:
	std::string mName;
	int getIndex(int cell_x, int cell_y);
	std::vector<Grid*> _grids;

	int  mWorldWidth;
	int  mWorldHeight;
	int  mCellWidth;
	int  mCellHeight;
	float  mDefaultValue;
private:
	Graph(float width, float height,int cell_width,int cell_height, float default_value);
	Graph();
	~Graph();


};


