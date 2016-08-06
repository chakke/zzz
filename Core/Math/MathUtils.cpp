#include "MathUtils.hpp"
float MathUtils::nanoToSec = 1 / 1000000000.0f;

float MathUtils::FLOAT_ROUNDING_ERROR = 0.000001f; // 32 bits
float MathUtils::PI = 3.1415927f;
float MathUtils::PI2 = MathUtils::PI * 2;

float MathUtils::E = 2.7182818f;

int MathUtils::SIN_BITS = 14; // 16KB. Adjust for accuracy.
int MathUtils::SIN_MASK = ~(-1 << MathUtils::SIN_BITS);
int MathUtils::SIN_COUNT = MathUtils::SIN_MASK + 1;

float MathUtils::radFull = MathUtils::PI * 2;
float MathUtils::degFull = 360;
float MathUtils::radToIndex = MathUtils::SIN_COUNT / radFull;
float MathUtils::degToIndex = MathUtils::SIN_COUNT / degFull;

/** multiply by this to convert from radians to degrees */
float MathUtils::radiansToDegrees = 180.0f / MathUtils::PI;
float MathUtils::radDeg = MathUtils::radiansToDegrees;
/** multiply by this to convert from degrees to radians */
float MathUtils::degreesToRadians = MathUtils::PI / 180;
float MathUtils::degRad = MathUtils::degreesToRadians;


bool MathUtils::isZero(float value) {
	return abs(value) <= MathUtils::FLOAT_ROUNDING_ERROR;
}

bool MathUtils::isZero(float value,float epsilon) {
	return abs(value) <= epsilon;
}