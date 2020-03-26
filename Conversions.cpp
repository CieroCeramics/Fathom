#include "Conversions.h"
//#include "Quaternion.h"
//#include "Matrix.h"

Conversions::Conversions()
{
}


Conversions::~Conversions()
{
}

std::string Conversions::intToString(int num)
{
	std::string convertedString;
	std::stringstream out;

	out << num;
	convertedString = out.str();

	return convertedString;
}

std::string Conversions::floatToString(float num)
{
	std::string convertedString;
	std::stringstream out;

	out << num;
	convertedString = out.str();

	return convertedString;
}

int stringToInt(const char* string)
{
	return atoi(string);
}

float stringToFloat(const char* string)
{
	return atof(string);
}

char* Conversions::numToCharArray(float &num)
{
	static char out[10];

	sprintf(out, "%f", num);

	return out;
}

char* Conversions::stringToCharArray(std::string string)
{
	char result[100];

	for (unsigned int i = 0; i < string.size(); ++i)
	{
		result[i] = string.at(i);
	}

	return result;
}

void Conversions::combineCharArrays(char* array1, char* array2) //BROKEN
{
	char result[100];
	strcat_s(result, array1);
	strcat_s(result, array2);
}

//Matrix Conversions::quaternionToMatrix(Quaternion &quaternion)
//{
//	Matrix result;
//	quaternion.normalize();
//	result.setSize(3, 3);
//	
//	float sqw = quaternion.getW() * quaternion.getW();
//    float sqx = quaternion.getX() * quaternion.getX();
//    float sqy = quaternion.getY() * quaternion.getY();
//    float sqz = quaternion.getZ() * quaternion.getZ();
//	
//    // invs (inverse square length) is only required if quaternion is not already normalised
//    double invs = 1 / (sqx + sqy + sqz + sqw);
//
//	result.setElement(0, sqx - sqy - sqz + sqw); // since sqw + sqx + sqy + sqz =1/invs*invs
//	result.setElement (5, -sqx + sqy - sqz + sqw);
//	result.setElement(10, -sqx - sqy + sqz + sqw);
//   
//    float tmp1 = quaternion.getX() * quaternion.getY();
//    float tmp2 = quaternion.getZ() * quaternion.getW();
//
//	result.setElement(4, 2.0 * (tmp1 + tmp2));
//	result.setElement(1, 2.0 * (tmp1 - tmp2));
//    
//	tmp1 = quaternion.getX() * quaternion.getZ();
//	tmp2 = quaternion.getY() * quaternion.getW();
//
//	result.setElement(8, 2.0 * (tmp1 - tmp2));
//	result.setElement(2, 2.0 * (tmp1 + tmp2));
//
//	tmp1 = quaternion.getY() * quaternion.getZ();
//	tmp2 = quaternion.getX() * quaternion.getW();
//
//	result.setElement(9, 2.0 * (tmp1 + tmp2));
//	result.setElement(6, 2.0 * (tmp1 - tmp2));     
// 
//	return result;
//}
//
//Quaternion Conversions::matrixToQuaternion(Matrix &matrix)
//{
//	//http://web.archive.org/web/20041029003853/http://www.j3d.org/matrix_faq/matrfaq_latest.html#Q55
//
//	Quaternion result;
//	float temp;
//
//	if (matrix.getTrace() > 0)
//	{
//		temp = sqrt(matrix.getTrace()) * 2;
//
//		result.setW(0.25 * temp);
//		result.setX((matrix.getElement(6) - matrix.getElement(9)) / temp);
//		result.setY((matrix.getElement(8) - matrix.getElement(2)) / temp);
//		result.setZ((matrix.getElement(1) - matrix.getElement(4)) / temp);		
//	}
//	else
//	{
//		temp = sqrt(1 + matrix.getElement(0) - matrix.getElement(5) - matrix.getElement(10)) * 2;
//
//		if (matrix.getElement(0) > matrix.getElement(5) && matrix.getElement(0) > matrix.getElement(10)) //Checks if element 0 is the biggest of the diagonal
//		{
//			result.setW((matrix.getElement(6) - matrix.getElement(9)) / temp);
//			result.setX(0.25 * temp);
//			result.setY((matrix.getElement(1) + matrix.getElement(4)) / temp);
//			result.setZ((matrix.getElement(8) + matrix.getElement(2)) / temp);
//		}
//		else if (matrix.getElement(5) > matrix.getElement(10)) //Checks if element 5 is biggest of the diagonal
//		{
//			result.setW((matrix.getElement(8) - matrix.getElement(2)) / temp);
//			result.setX((matrix.getElement(1) + matrix.getElement(4)) / temp);
//			result.setY(0.25 * temp);
//			result.setZ((matrix.getElement(6) + matrix.getElement(9)) / temp);
//		}
//		else //If element 10 is the biggest of the diagonal
//		{
//			result.setW((matrix.getElement(1) - matrix.getElement(4)) / temp);
//			result.setX((matrix.getElement(8) + matrix.getElement(2)) / temp);
//			result.setY((matrix.getElement(6) + matrix.getElement(9)) / temp);
//			result.setZ(0.25 * temp);
//		}
//	}
//
//	result.clean();
//
//	return result;
//}