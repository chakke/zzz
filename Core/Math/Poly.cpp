#include "Poly.hpp"


Poly::Poly()
{
	reset();
}

Poly::Poly(std::vector<float> vertices)
{
	reset();
	this->setVertices(vertices);
}

std::vector<float> Poly::getVertices()
{
	return this->localVertices;
}

std::vector<float> Poly::getTransformedVertices()
{
	if (!dirty) return worldVertices;
	dirty = false;
	std::vector<float> localVertices (this->localVertices);
	worldVertices.clear();

	
	const float positionX = this->x;
	const float positionY = this->y;
	const float originX = this->originX;
	const float originY = this->originY;
	const float scaleX = this->scaleX;
	const float scaleY = this->scaleY;
	const bool scale = scaleX != 1 || scaleY != 1;
	const float rotation = this->rotation;
	const float c = cos(rotation);
	const float s = sin(rotation);

	for (int i = 0, n = worldVertices.size(); i < n; i += 2) {
		float x = localVertices[i] - originX;
		float y = localVertices[i + 1] - originY;

		// scale if needed
		if (scale) {
			x *= scaleX;
			y *= scaleY;
		}

		// rotate if needed
		if (rotation != 0) {
			float oldX = x;
			x = c * x - s * y;
			y = s * oldX + c * y;
		}

		worldVertices[i] = positionX + x + originX;
		worldVertices[i + 1] = positionY + y + originY;
	}
	return worldVertices;
}

void Poly::setOrigin(float x, float y)
{
	this->originX = x;
	this->originY = y;
	this->setDirty(true);
}

void Poly::setVertices(std::vector<float> vertices)
{
	if (vertices.size() < 6) {
		throw std::invalid_argument("Polys must contain at least 3 points.");
	}
	localVertices.clear();
	for (auto x : vertices) {
		localVertices.push_back(x);
	}
	this->setDirty(true);
}

void Poly::translate(float x, float y)
{
	this->x += x;
	this->y += y;
	this->setDirty(true);
}

void Poly::setRotation(float degrees)
{
	this->rotation = degrees;
	this->setDirty(true);
}

void Poly::rotate(float degrees)
{
	this->rotation += degrees;
	this->setDirty(true);
}

void Poly::setScale(float scaleX, float scaleY)
{
	this->scaleX = scaleX;
	this->scaleY = scaleY;
	this->setDirty(true);
}

void Poly::scale(float amount)
{
	this->scaleX += amount;
	this->scaleY += amount;
	this->setDirty(true);
}

void Poly::setDirty(bool d)
{
	dirty = d;
}

float Poly::area()
{
	std::vector<float> Poly = getVertices();
	int offset = 0;
	int count = Poly.size();
	float area = 0;
	for (int i = offset, n = offset + count; i < n; i += 2) {
		int x1 = i;
		int y1 = i + 1;
		int x2 = (i + 2) % n;
		if (x2 < offset)
			x2 += offset;
		int y2 = (i + 3) % n;
		if (y2 < offset)
			y2 += offset;
		area += Poly[x1] * Poly[y2];
		area -= Poly[x2] * Poly[y1];
	}
	area *= 0.5f;
	return area;
}

Rect Poly::getBoundingBox()
{
	std::vector<float> vertices = getTransformedVertices();

	float minX = vertices[0];
	float minY = vertices[1];
	float maxX = vertices[0];
	float maxY = vertices[1];

	int numFloats = vertices.size();
	for (int i = 2; i < numFloats; i += 2) {
		minX = minX > vertices[i] ? vertices[i] : minX;
		minY = minY > vertices[i + 1] ? vertices[i + 1] : minY;
		maxX = maxX < vertices[i] ? vertices[i] : maxX;
		maxY = maxY < vertices[i + 1] ? vertices[i + 1] : maxY;
	}	
	bounds.setRect(minX,minY, maxX - minX, maxY - minY);
	return bounds;
}

bool Poly::contains(float x, float y)
{
	std::vector<float> vertices = getTransformedVertices();
	int numFloats = vertices.size();
	short intersects = 0;

	for (int i = 0; i < numFloats; i += 2) {
		float x1 = vertices[i];
		float y1 = vertices[i + 1];
		float x2 = vertices[(i + 2) % numFloats];
		float y2 = vertices[(i + 3) % numFloats];
		if (((y1 <= y && y < y2) || (y2 <= y && y < y1)) && x < ((x2 - x1) / (y2 - y1) * (y - y1) + x1)) intersects++;
	}
	return (intersects & 1) == 1;
}

bool Poly::contains(Vec2 point)
{
	return this->contains(point.x,point.y);
}

float Poly::getX()
{
	return x;
}

float Poly::getY()
{
	return y;
}

float Poly::getOriginX()
{
	return originX;
}

float Poly::getOriginY()
{
	return originY;
}

float Poly::getRotation()
{
	return rotation;
}

float Poly::getScaleX()
{
	return scaleX;
}

float Poly::getScaleY()
{
	return scaleY;
}

void Poly::reset()
{
	scaleX = 1;
	scaleY = 1;
	originX = 0;
	originY = 0;
	x = 0;
	y = 0;
	rotation = 0;
	dirty = true;
}
