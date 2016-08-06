
#include "Vector2.hpp"
#include "MathUtils.hpp"

	Vector2::Vector2(float x, float y) : x(x), y(y)
	{
		this->retain();
		this->autorelease();
	}

	Vector2::Vector2(Vector2 * other) : x(other->getX()), y(other->getY())
	{
		this->retain();
		this->autorelease();
	}

	Vector2::Vector2() : x(0),y(0)
	{
		this->retain();
		this->autorelease();
	}

	Vector2::Vector2(cocos2d::Vec2 pos) : x(pos.x),y(pos.y)
	{
		this->retain();
		this->autorelease();
	}

	Vector2::~Vector2()
	{
	}

	Vector2 * Vector2::copy()
	{
		auto clone = new Vector2(this);
		clone->release();
		return clone;
	}

	Vector2 * Vector2::set(cocos2d::Vec2 other)
	{
		this->set(other.x, other.y);
		return this;
	}

	Vector2 * Vector2::set(Vector2 * other)
	{
		this->set(other->getX(), other->getY());
		return this;
	}

	Vector2 * Vector2::set(float x, float y)
	{
		setX(x);
		setY(y);
		return this;
	}

	Vector2 * Vector2::sub(cocos2d::Vec2 other)
	{
		this->setX(this->getX() - other.x);
		this->setY(this->getY() - other.y);
		return this;
	}

	Vector2 * Vector2::sub(Vector2 * other)
	{
		this->setX(this->getX() - other->getX());
		this->setY(this->getY() - other->getY());
		return this;
	}

	Vector2 * Vector2::sub(float x, float y)
	{
		this->setX(this->getX() - x);
		this->setY(this->getY() - y);
		return this;
	}

	Vector2 * Vector2::add(cocos2d::Vec2 other)
	{
		this->setX(this->getX() + other.x);
		this->setY(this->getY() + other.y);
		return this;
	}

	Vector2 * Vector2::add(Vector2 * other)
	{
		this->setX(this->getX() + other->getX());
		this->setY(this->getY() + other->getY());
		return this;
	}

	Vector2 * Vector2::add(float x, float y)
	{
		this->setX(this->getX() + x);
		this->setY(this->getY() + x);
		return this;
	}

	Vector2 * Vector2::scl(float scale)
	{
		this->setX(this->getX()*scale);
		this->setY(this->getY()*scale);
		return this;
	}

	Vector2 * Vector2::scl(float x, float y)
	{
		this->setX(this->getX()*x);
		this->setY(this->getY()*y);
		return this;
	}

	Vector2 * Vector2::scl(cocos2d::Vec2 other)
	{
		this->setX(this->getX() * other.x);
		this->setY(this->getY() * other.y);
		return this;
	}

	Vector2 * Vector2::scl(Vector2 * other)
	{
		this->setX(this->getX() * other->getX());
		this->setY(this->getY() * other->getY());
		return this;
	}

	Vector2 * Vector2::limit(float limit)
	{

		return limit2(limit*limit);
	}

	Vector2 * Vector2::limit2(float limit2)
	{
		float len2 = this->len2();
		if (len2 > limit2) {
			return this->scl(float(sqrt(limit2 / len2)));
		}
		return this;
	}

	Vector2 * Vector2::lerp(Vector2 * target, float alpha)
	{
		float invAlpha = 1.0f - alpha;
		this->setX(this->getX() * invAlpha + target->getX() * alpha);
		this->setY(this->getY() * invAlpha + target->getY() * alpha);
		return this;
	}

	Vector2 * Vector2::lerp(cocos2d::Vec2 target, float alpha)
	{
		float invAlpha = 1.0f - alpha;
		this->setX(this->getX() * invAlpha + target.x * alpha);
		this->setY(this->getY() * invAlpha + target.x * alpha);
		return this;
	}

	Vector2 * Vector2::clamp(float min, float max)
	{
		float len2 = this->len2();
		if (len2 == 0) return this;
		float max2 = max * max;
		if (len2 > max2) return scl((float)sqrt(max2 / len2));
		float min2 = min * min;
		if (len2 < min2) return scl((float)sqrt(min2 / len2));
		return this;
	}

	Vector2 * Vector2::setLength(float len)
	{
		return setLength2(len * len);
	}

	Vector2 * Vector2::setLength2(float len2)
	{
		float oldLen2 = this->len2();
		return (oldLen2 == 0 || oldLen2 == len2) ? this : scl((float)sqrt(len2 / oldLen2));
	}

	std::string Vector2::toString()
	{
		return cocos2d::StringUtils::format("%f , %f", this->getX(), this->getY()).c_str();
	}

	bool Vector2::equal(float x, float y)
	{
		return this->getX() == x && this->getY() == y;
	}

	bool Vector2::equal(cocos2d::Vec2  other)
	{
		return equal(other.x, other.y);
	}

	bool Vector2::equal(Vector2 * other)
	{
		return this->equal(other->getX(), other->getY());
	}

	bool Vector2::epsilonEquals(float x, float y, float epsilon)
	{

		if (abs(x - this->getX()) > epsilon) return false;
		if (abs(y - this->getY()) > epsilon) return false;
		return true;
	}

	bool Vector2::epsilonEquals(cocos2d::Vec2  other, float epsilon)
	{
		return epsilonEquals(other.x, other.y, epsilon);
	}

	bool Vector2::epsilonEquals(Vector2 * other, float epsilon)
	{
		return epsilonEquals(other->getX(), other->getY(), epsilon);
	}

	bool Vector2::isZero()
	{
		return this->getX() == 0 && this->getY() == 0;
	}

	float Vector2::len()
	{
		return sqrt(this->getX()*this->getX() + this->getY()*this->getY());
	}

	float Vector2::len2()
	{
		return this->getX()*this->getX() + this->getY()*this->getY();
	}

	float Vector2::dst(cocos2d::Vec2  other)
	{
		return dst(other.x, other.y);
	}

	float Vector2::dst(Vector2 * other)
	{
		return dst(other->getX(), other->getY());
	}

	float Vector2::dst(float x, float y)
	{
		float dx = this->getX() - x;
		float dy = this->getY() - y;
		return sqrt(dx*dx + dy*dy);
	}

	float Vector2::dst2(cocos2d::Vec2 other)
	{
		return dst2(other.x, other.y);
	}

	float Vector2::dst2(Vector2 * other)
	{
		return dst2(other->getX(), other->getY());
	}

	float Vector2::dst2(float x, float y)
	{
		float dx = x - this->getX();
		float dy = y - this->getY();
		return dx*dx + dy*dy;
	}

	float Vector2::dot(float x, float y)
	{
		return this->getX()*x + this->getY()*y;
	}

	float Vector2::dot(cocos2d::Vec2 val)
	{
		return dot(val.x, val.y);
	}

	float Vector2::dot(Vector2 * val)
	{
		return dot(val->getX(), val->getY());
	}

	float Vector2::crs(float x, float y)
	{
		return this->getX()*y - this->getY()*x;
	}

	float Vector2::crs(cocos2d::Vec2 val)
	{
		return crs(val.x, val.y);
	}

	float Vector2::crs(Vector2 * val)
	{
		return crs(val->getX(), val->getY());
	}

	Vector2 * Vector2::normalize()
	{
		float len = this->len();
		if (len != 0) {
			return this->scl(1 / len);
		}
		return this;
	}

	Vector2 * Vector2::setZero()
	{
		return this->set(0, 0);
	}

	Vector2 * Vector2::setX(float x)
	{
		this->x = x;
		return this;
	}

	Vector2 * Vector2::setY(float y)
	{
		this->y = y;
		return this;
	}

	float Vector2::getX()
	{
		return this->x;
	}

	float Vector2::getY()
	{
		return this->y;
	}

	float Vector2::angle()
	{
		float angle = (float)atan2(y, x) * MathUtils::radiansToDegrees;
		if (angle < 0) angle += 360;
		return angle;
	}

	float Vector2::angle(float x, float y)
	{
		return (float)atan2(crs(x, y), dot(x, y)) * MathUtils::radiansToDegrees;
	}

	float Vector2::angle(cocos2d::Vec2 other)
	{
		return angle(other.x, other.y);
	}

	float Vector2::angle(Vector2 * other)
	{
		return angle(other->getX(), other->getY());
	}

	float Vector2::angleRad()
	{
		return (float)atan2(this->getY(), this->getX());
	}

	float Vector2::angleRad(float x, float y)
	{
		return (float)atan2(crs(x, y), dot(x, y));
	}

	float Vector2::angleRad(cocos2d::Vec2 other)
	{
		return angleRad(other.x, other.y);
	}

	float Vector2::angleRad(Vector2 * other)
	{
		return angleRad(other->getX(), other->getY());
	}

	Vector2 * Vector2::setAngle(float degrees)
	{
		return this->setAngleRad(degrees * MathUtils::degreesToRadians);
	}

	Vector2 * Vector2::setAngleRad(float radians)
	{
		this->set(this->len(), 0.0f);
		this->rotateRad(radians);
		return this;
	}

	Vector2 * Vector2::rotate(float degrees)
	{
		return this->rotateRad(degrees * MathUtils::degreesToRadians);
	}

	Vector2 * Vector2::rotateRad(float radians)
	{
		float c = (float)cos(radians);
		float s = (float)sin(radians);

		float newX = this->getX() * c - this->getY() * s;
		float newY = this->getX() * s + this->getY()* c;

		this->setX(newX);
		this->setY(newY);

		return this;
	}

	bool Vector2::isOnLine(float x, float y)
	{
		return MathUtils::isZero(this->getX() * y - this->getY() *x);
	}

	bool Vector2::isOnLine(cocos2d::Vec2 other)
	{
		return this->isOnLine(other.x, other.y);
	}

	bool Vector2::isOnLine(Vector2 * other)
	{
		return this->isOnLine(other->getX(), other->getY());
	}

	bool Vector2::isOnLine(float x, float y, float epsilon)
	{
		return MathUtils::isZero(this->getX() * y - this->getY() *x, epsilon);
	}

	bool Vector2::isOnLine(cocos2d::Vec2 other, float epsilon)
	{
		return this->isOnLine(other.x, other.y, epsilon);
	}

	bool Vector2::isOnLine(Vector2 * other, float epsilon)
	{
		return this->isOnLine(other->getX(), other->getY(), epsilon);
	}

	bool Vector2::isCollinear(float x, float y)
	{
		return this->isOnLine(x, y) && this->dot(x, y) > 0.0f;
	}

	bool Vector2::isCollinear(cocos2d::Vec2 other)
	{
		return this->isCollinear(other.x, other.y);
	}

	bool Vector2::isCollinear(Vector2 * other)
	{
		return this->isCollinear(other->getX(), other->getY());
	}

	bool Vector2::isCollinear(float x, float y, float epsilon)
	{
		return this->isOnLine(x, y, epsilon) && this->dot(x, y) > 0.0f;
	}

	bool Vector2::isCollinear(cocos2d::Vec2 other, float epsilon)
	{
		return this->isCollinear(other.x, other.y, epsilon);
	}

	bool Vector2::isCollinear(Vector2 * other, float epsilon)
	{
		return this->isCollinear(other->getX(), other->getY(), epsilon);
	}

	bool Vector2::isCollinearOpposite(float x, float y)
	{
		return this->isOnLine(x, y) && this->dot(x, y) < 0.0f;
	}

	bool Vector2::isCollinearOpposite(cocos2d::Vec2 other)
	{

		return this->isCollinearOpposite(other.x, other.y);
	}

	bool Vector2::isCollinearOpposite(Vector2 * other)
	{
		return this->isCollinearOpposite(other->getX(), other->getY());
	}

	bool Vector2::isCollinearOpposite(float x, float y, float epsilon)
	{
		return this->isOnLine(x, y, epsilon) && this->dot(x, y) < 0.0f;
	}

	bool Vector2::isCollinearOpposite(cocos2d::Vec2 other, float epsilon)
	{
		return this->isCollinearOpposite(other.x, other.y, epsilon);
	}

	bool Vector2::isCollinearOpposite(Vector2 * other, float epsilon)
	{
		return isCollinearOpposite(other->getX(), other->getY(), epsilon);
	}

	bool Vector2::isPerpendicular(float x, float y)
	{
		return MathUtils::isZero(dot(x, y));
	}

	bool Vector2::isPerpendicular(cocos2d::Vec2 other)
	{
		return MathUtils::isZero(dot(other.x, other.y));
	}

	bool Vector2::isPerpendicular(Vector2 * other)
	{
		return this->isPerpendicular(other->getX(), other->getY());
	}

	bool Vector2::isPerpendicular(float x, float y, float epsilon)
	{
		return MathUtils::isZero(dot(x, y), epsilon);
	}

	bool Vector2::isPerpendicular(cocos2d::Vec2 other, float epsilon)
	{
		return this->isPerpendicular(other.x, other.y, epsilon);
	}

	bool Vector2::isPerpendicular(Vector2 * other, float epsilon)
	{
		return this->isPerpendicular(other->getX(), other->getY(), epsilon);
	}

	bool Vector2::hasSameDirection(float x, float y)
	{
		return this->dot(x, y) > 0;
	}

	bool Vector2::hasSameDirection(cocos2d::Vec2 other)
	{
		return this->hasSameDirection(other.x, other.y);
	}

	bool Vector2::hasSameDirection(Vector2 * other)
	{
		return this->hasSameDirection(other->getX(), other->getY());
	}

	bool Vector2::hasOppositeDirection(float x, float y)
	{
		return this->dot(x, y) < 0;
	}

	bool Vector2::hasOppositeDirection(cocos2d::Vec2 other)
	{
		return this->hasOppositeDirection(other.x, other.y);
	}

	bool Vector2::hasOppositeDirection(Vector2 * other)
	{
		return this->hasOppositeDirection(other->getX(), other->getY());
	}

	Vec2 Vector2::toVec2()
	{
		return Vec2(this->getX(), this->getY());
	}
