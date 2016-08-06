#include "ShapeComponent.hpp"


ShapeComponent::ShapeComponent(Shape * shape)
{
	this->mShape = shape;
}

ShapeComponent::~ShapeComponent()
{
	CC_SAFE_DELETE(mShape);
}

Shape * ShapeComponent::getShape()
{
	return mShape;
}
