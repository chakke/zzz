#pragma once
#include "cocos2d.h"
USING_NS_CC; 

/*
Written by Badlogic
Arcade Dota
20-04-2016
*/

class MathUtils {
public:
	static float nanoToSec;

	// ---
	static  float FLOAT_ROUNDING_ERROR; // 32 bits
	static  float PI ;
	static  float PI2;

	static  float E;

	static int SIN_BITS ; // 16KB. Adjust for accuracy.
	static int SIN_MASK ;
	static int SIN_COUNT;

	static  float radFull;
	static  float degFull;
	static  float radToIndex;
	static  float degToIndex;

	/** multiply by this to convert from radians to degrees */
	static  float radiansToDegrees;
	static  float radDeg;
	/** multiply by this to convert from degrees to radians */
	static  float degreesToRadians;
	static  float degRad;

	static bool isZero(float value);
	static bool isZero(float value,float epsilon);
};
