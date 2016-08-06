#pragma once

#include "cocos2d.h"
#include "../../artemis/Component.h"
#include "Core/Shapes/Shapes.hpp"
class ShapeComponent : public artemis::Component {

public:
	ShapeComponent(Shape* shape);
	~ShapeComponent();

	Shape* getShape();
protected:
	Shape* mShape;
};
