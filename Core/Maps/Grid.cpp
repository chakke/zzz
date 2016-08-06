
#include "Grid.hpp"

Grid::Grid(int x, int y, float value, Grid::Type type) : x(x), y(y), value(value), type(type)
{
	
}

void Grid::setType(Grid::Type type)
{
	this->type = type;
}

Grid::Type Grid::getType()
{
	return type;
}

void Grid::setGrid(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Grid::setValue(float value)
{
	this->value = value;
}

float Grid::getValue()
{
	return this->value;
}

int Grid::getX()
{
	return x;
}

int Grid::getY()
{
	return y;
}

bool Grid::hasEntities()
{
	return _entities.size() > 0;
}

void Grid::removeAllEntities()
{
	_entities.clear();
}

std::vector<int> Grid::getEntities()
{
	return _entities;
}

void Grid::addEntity(int id)
{
	_entities.push_back(id);
}


