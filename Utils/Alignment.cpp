#include "Alignment.h"

void Alignment::setPosition(cocos2d::Node* node, float x, float y, Align align){
	Alignment::setX(node, x, align);
	Alignment::setY(node, y, align);
}

cocos2d::Vec2 Alignment::getPosition(cocos2d::Node* node, Align align){
	return cocos2d::Vec2(Alignment::getX(node, align), Alignment::getY(node, align));
}
void Alignment::setX(cocos2d::Node* node, float x, Align align){

	cocos2d::Size size = node->getContentSize();
	cocos2d::Vec2 anchorPoint = node->getAnchorPoint();


	if (node->isIgnoreAnchorPointForPosition())
	{
		float cx = x;
		if (align == Align::RIGHT || align == Align::BOTTOM_RIGHT || align == Align::TOP_RIGHT){
			cx = x - size.width;
		}
		else if (align == Align::CENTER || align == Align::TOP || align == Align::BOTTOM){
			cx = x - size.width / 2;
		}
		node->setPositionX(cx - (.5f - anchorPoint.x)*size.width);
	}
	else
	{
		float cx = x;
		if (align == Align::RIGHT || align == Align::BOTTOM_RIGHT || align == Align::TOP_RIGHT){
			cx = x - size.width / 2;
		}
		else if (align == Align::LEFT || align == Align::TOP_LEFT || align == Align::BOTTOM_LEFT){
			cx = x + size.width / 2;
		}
		node->setPositionX(cx - (.5f - anchorPoint.x)*size.width);
	}

}
void Alignment::setY(cocos2d::Node* node, float y, Align align){
	cocos2d::Size size = node->getContentSize();
	cocos2d::Vec2 anchorPoint = node->getAnchorPoint();
	if (node->isIgnoreAnchorPointForPosition())
	{

		float cy = y;
		if (align == Align::TOP || align == Align::TOP_LEFT || align == Align::TOP_RIGHT){
			cy = y - size.height;
		}
		else if (align == Align::LEFT || align == Align::CENTER || align == Align::RIGHT){
			cy = y - size.height / 2;
		}
		node->setPositionY(cy - (.5f - anchorPoint.y)*size.height);
	}
	else
	{
		float cy = y;
		if (align == Align::TOP || align == Align::TOP_LEFT || align == Align::TOP_RIGHT){
			cy = y - size.height / 2;
		}
		else if (align == Align::BOTTOM_LEFT || align == Align::BOTTOM || align == Align::BOTTOM_RIGHT){
			cy = y + size.height / 2;
		}
		node->setPositionY(cy - (.5f - anchorPoint.y)*size.height);
	}
}

float Alignment::getX(cocos2d::Node* node, Align align){
	cocos2d::Size size = node->getContentSize();
	cocos2d::Vec2 position = node->getPosition();
	cocos2d::Vec2 anchorPoint = node->isIgnoreAnchorPointForPosition() ? cocos2d::Vec2(0, 0) : node->getAnchorPoint();

	if (align == Align::RIGHT || align == Align::BOTTOM_RIGHT || align == Align::TOP_RIGHT){
		return position.x + (1 - anchorPoint.x)*size.width;
	}
	else if (align == Align::TOP || align == Align::CENTER || align == Align::BOTTOM){
		return position.x + (.5f - anchorPoint.x)*size.width;
	}
	return	position.x - anchorPoint.x*size.width;
}
float Alignment::getY(cocos2d::Node* node, Align align){
	cocos2d::Size size = node->getContentSize();
	cocos2d::Vec2 position = node->getPosition();
	cocos2d::Vec2 anchorPoint = node->isIgnoreAnchorPointForPosition() ? cocos2d::Vec2(0, 0) : node->getAnchorPoint();

	if (align == Align::TOP_LEFT || align == Align::TOP || align == Align::TOP_RIGHT){
		return position.y + (1 - anchorPoint.y)*size.height;
	}
	else if (align == Align::LEFT || align == Align::CENTER || align == Align::RIGHT){
		return position.y + (.5f - anchorPoint.y)* size.height;
	}
	return	position.y - anchorPoint.y*size.height;
}
