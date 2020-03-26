#pragma once
#include <string>
#include <sstream>
#include <math.h>

#define FE_PI 3.14159265358979323846
#define mRadToDeg(radians) ((radians) * (180 / FE_PI)) //Macro
#define mDegToRad(degrees) ((degrees) * (FE_PI / 180)) //Macro

class Quaternion; //wtfmagic
class Matrix;

class Conversions
{
public:
	Conversions();
	~Conversions();

	//Angle stuff
	//static float radToDeg(float radians);
	//static float degToRad(float degrees);

	//String and Char Arrays
	static std::string intToString(int num);
	static std::string floatToString(float num);
	static int stringToInt(const char* string);
	static float stringToFloat(const char* string);
	static char* numToCharArray(float &num);	
	static char* stringToCharArray(std::string string);
	static void combineCharArrays(char* array1, char* array2);

	//Quaternion and Matrix Conversion
	static Quaternion matrixToQuaternion(Matrix &matrix);
	static Matrix quaternionToMatrix(Quaternion &quaternion);

private:
};

