#include "Shape.hpp"

Shape::Shape() : x(0),y(0)
{
}

Shape::~Shape()
{
}

void Shape::setPosition(float x, float y, const game::Align align)
{
	this->x = x;
	this->y = y;
}

void Shape::setPositionX(float x,const game::Align align)
{
	this->x = x;
}

void Shape::setPositionY(float y, const game::Align align)
{
	this->y = y;
}

float Shape::getPositionX(const game::Align align)
{
	return this->x;
}

float Shape::getPositionY(const game::Align align)
{
	return this->y;
}
