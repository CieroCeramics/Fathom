/*

- Note that currently it does not support error checking for sizes
	- IE) If you assign a value to element 4 in a 3x3, it'll work, just wont be used for certain calculations
-	Only multiplication, determinants and inverse use the matrix size


- Remember, all rotation matricies have a determinant of one
	- Something to keep in mind if it's necessary to use sometime in the future
	- We could also probably add a check to see if it's a rotation matrix and then inverse it by transposing instead
*/

#include "Matrix.h"
#include "Include.h"


Matrix::Matrix()
{
	//Defaults to 4x4

	for (unsigned int i = 0; i < 16; ++i)
	{
		_element[i] = 0;
	}

	_column = 4;
	_row = 4;
}

Matrix::Matrix(Vector3f vector)
{
	for (unsigned int i = 0; i < 16; ++i)
	{
		_element[i] = 0;
	}

	_element[0] = vector.getX();
	_element[4] = vector.getY();
	_element[8] = vector.getZ();
	_element[12] = 1.0f;

	_column = 4;
	_row = 1;
}

Matrix::Matrix(Vector3f rotate, Vector3f translation, Vector3f scale)
{
	makeHomogenous(rotate, translation, scale);
}

Matrix::~Matrix()
{
}

void Matrix::makeHomogenous(Vector3f rotate, Vector3f translation, Vector3f scale)
{
	//XYZ. Fuck this is so bad.

	if (rotate.getX() == 0 && rotate.getY() == 0 && rotate.getZ() == 0) //If rotations are 0 then we don't need to rotate now do we?
	{
		_element[0] = scale.getX();
		_element[1] = 0.0f;
		_element[2] = 0.0f;		

		_element[4] = 0.0f;
		_element[5] = scale.getY();
		_element[6] = 0.0f;		

		_element[8] = 0.0f;
		_element[9] = 0.0f;
		_element[10] = scale.getZ();	
	}
	else
	{
		Matrix xRotation;
		Matrix yRotation;
		Matrix zRotation;
		Matrix scaleMatrix;
	
		xRotation.setSize(3, 3);
		yRotation.setSize(3, 3);
		zRotation.setSize(3, 3);
		scaleMatrix.setSize(3, 3);

		float currentCos = cos(mDegToRad(rotate.getX()));
		float currentSin = sin(mDegToRad(rotate.getX()));

		xRotation.setElement(0, 1.0f);
		xRotation.setElement(5, currentCos);
		xRotation.setElement(6, -currentSin);
		xRotation.setElement(9, currentSin);
		xRotation.setElement(10, currentCos);

		currentCos = cos(mDegToRad(rotate.getY()));
		currentSin = sin(mDegToRad(rotate.getY()));

		yRotation.setElement(0, currentCos);
		yRotation.setElement(2, currentSin);
		yRotation.setElement(5, 1.0f);
		yRotation.setElement(8, -currentSin);
		yRotation.setElement(10, currentCos);

		currentCos = cos(mDegToRad(rotate.getZ()));
		currentSin = sin(mDegToRad(rotate.getZ()));

		zRotation.setElement(0, currentCos);
		zRotation.setElement(1, -currentSin);
		zRotation.setElement(4, currentSin);
		zRotation.setElement(5, currentCos);
		zRotation.setElement(10, 1.0f);

		scaleMatrix.setElement(0, scale.getX());
		scaleMatrix.setElement(5, scale.getY());
		scaleMatrix.setElement(10, scale.getZ());
		scaleMatrix.setElement(15, 1.0f);

		Matrix rotationMatrix;
		rotationMatrix.setSize(3, 3);
		rotationMatrix = zRotation.multiply(yRotation);
		rotationMatrix.setSize(3, 3);
		rotationMatrix = rotationMatrix.multiply(xRotation);
		rotationMatrix.setSize(3, 3);
		rotationMatrix = scaleMatrix.multiply(rotationMatrix);
		rotationMatrix.setSize(3, 3);

		_element[0] = rotationMatrix.getElement(0);
		_element[1] = rotationMatrix.getElement(1);
		_element[2] = rotationMatrix.getElement(2);		

		_element[4] = rotationMatrix.getElement(4);
		_element[5] = rotationMatrix.getElement(5);
		_element[6] = rotationMatrix.getElement(6);		

		_element[8] = rotationMatrix.getElement(8);
		_element[9] = rotationMatrix.getElement(9);
		_element[10] = rotationMatrix.getElement(10);		
	}

	_element[3] = translation.getX();
	_element[7] = translation.getY();
	_element[11] = translation.getZ();

	_element[12] = 0.0f;
	_element[13] = 0.0f;
	_element[14] = 0.0f;
	_element[15] = 1.0f;
	
	_column = 4;
	_row = 4;

	//clean();
}

void Matrix::makeHomogenousV2(Matrix rotationMatrix, Vector3f translation, Vector3f scale)
{
	//XYZ. Fuck this is so bad.
	//Changed rotational order to ZYX for skeletons

	Matrix scaleMatrix;
	
	scaleMatrix.setSize(3, 3);

	scaleMatrix.setElement(0, scale.getX());
	scaleMatrix.setElement(5, scale.getY());
	scaleMatrix.setElement(10, scale.getZ());
	scaleMatrix.setElement(15, 1.0f);

	_element[0] = rotationMatrix.getElement(0);
	_element[1] = rotationMatrix.getElement(1);
	_element[2] = rotationMatrix.getElement(2);
	_element[3] = translation.getX();

	_element[4] = rotationMatrix.getElement(4);
	_element[5] = rotationMatrix.getElement(5);
	_element[6] = rotationMatrix.getElement(6);
	_element[7] = translation.getY();

	_element[8] = rotationMatrix.getElement(8);
	_element[9] = rotationMatrix.getElement(9);
	_element[10] = rotationMatrix.getElement(10);
	_element[11] = translation.getZ();

	_element[12] = 0.0f;
	_element[13] = 0.0f;
	_element[14] = 0.0f;
	_element[15] = 1.0f;

	_column = 4;
	_row = 4;

	//clean();
}

void Matrix::setSize(unsigned int column, unsigned int row)
{
	_column = column;
	_row = row;
}

unsigned int Matrix::getSize(unsigned int element) //0 for column, 1 for row
{
	if (element == NG_COLUMN)
	{
		return _column;
	}
	else
	{
		return _row;
	}
}

void Matrix::setElement(unsigned int index, float value)
{
	_element[index] = value;
}

float Matrix::getElement(unsigned int index)
{
	return _element[index];
}

void Matrix::set(float* elements)
{
	for (unsigned int i = 0; i < 16; ++i)
	{
		_element[i] = elements[i];
	}
}

float* Matrix::get()
{
	return _element;
}

Matrix Matrix::getRotationMatrix() //ONLY WORKS WITH 4X4 HOMO MATRIX
{
	Matrix result = *this;
	result.setSize(3, 3);

	return result;
}

Vector3f Matrix::getTranslationVector() //ONLY WORKS WITH 4X4 HOMO MATRIX
{
	Vector3f result = Vector3f(_element[3], _element[7], _element[11]);

	return result;
}

Vector3f Matrix::getColVector(int col) //Returns the first column
{
	Vector3f result = Vector3f(_element[col], _element[col+4], _element[col+8]);

	return result;
}

float* Matrix::getRow(unsigned int row) //Returns the matrix in a float array. Does not account for size
{
	float result[4];
	unsigned int startingPoint = row * 4;

	result[0] = _element[startingPoint];
	result[1] = _element[++startingPoint];
	result[2] = _element[++startingPoint];
	result[3] = _element[++startingPoint];

	return result;
}

Matrix Matrix::add(Matrix &otherMatrix)
{
	Matrix result;

	for (unsigned int i = 0; i < 16; ++i)
	{
		result.setElement(i, _element[i] + otherMatrix.getElement(i));
	}

	return result;
}

Matrix Matrix::subtract(Matrix &otherMatrix)
{
	Matrix result;

	for (unsigned int i = 0; i < 16; ++i)
	{
		result.setElement(i, _element[i] - otherMatrix.getElement(i));
	}

	return result;
}

Matrix Matrix::multiply(Matrix &otherMatrix)
{
	Matrix result;

	if (_row == otherMatrix.getSize(NG_COLUMN))
	{
		for (unsigned int i = 0; i < 16; ++i)
		{
			unsigned int startColumn = i % 4;
			unsigned int startRow;	

			if (i < 4)
			{
				startRow = 0;
			}
			else if (i < 8)
			{
				startRow = 4;
			}
			else if (i < 12)
			{
				startRow = 8;
			}
			else
			{
				startRow = 12;
			}

			result.setElement(i, _element[startRow] * otherMatrix.getElement(startColumn) 
							   + _element[startRow + 1] * otherMatrix.getElement(startColumn + 4)
							   + _element[startRow + 2] * otherMatrix.getElement(startColumn + 8)
							   + _element[startRow + 3] * otherMatrix.getElement(startColumn + 12));
		}
	}
	else
	{
		std::cerr << "ERROR: CANNOT MULTIPLY MATRIX" << std::endl;
	}	

	//result.clean();

	return result;
}

Vector3f Matrix::multiply(Vector3f &vector) //4x4 only
{
	Vector3f result;

	result.setX(_element[0] * vector.getX() + _element[1] * vector.getY() + _element[2] * vector.getZ() + _element[3] * 1);
	result.setY(_element[4] * vector.getX() + _element[5] * vector.getY() + _element[6] * vector.getZ() + _element[7] * 1);
	result.setZ(_element[8] * vector.getX() + _element[9] * vector.getY() + _element[10] * vector.getZ() + _element[11] * 1);

	return result;
}

Matrix Matrix::multiply(float scalar)
{
	Matrix result;

	for (unsigned int i = 0; i < 16; ++i)
	{
		result.setElement(i, _element[i] * scalar);
	}

	return result;
}


Matrix Matrix::getInverse() //Omfg
{
	Matrix result;

	if (_column == _row)
	{
		float determinant = getDeterminant();

		if (_column == 4 || determinant != 0)
		{
			if (_column == 2)
			{
				result.setElement(0, _element[5]);
				result.setElement(1, -_element[1]);
				result.setElement(4, -_element[4]);
				result.setElement(5, _element[0]);

				result = result.multiply(1 / determinant);
			}
			else if (_column == 3)
			{
				result.setElement(0, _element[5] * _element[10] - _element[6] * _element[9]);
				result.setElement(1, _element[2] * _element[9] - _element[1] * _element[10]);
				result.setElement(2, _element[1] * _element[6] - _element[2] * _element[5]);

				result.setElement(4, _element[6] * _element[8] - _element[4] * _element[10]);
				result.setElement(5, _element[0] * _element[10] - _element[2] * _element[8]);
				result.setElement(6, _element[2] * _element[4] - _element[0] * _element[6]);

				result.setElement(8, _element[4] * _element[9] - _element[5] * _element[8]);
				result.setElement(9, _element[1] * _element[8] - _element[0] * _element[9]);
				result.setElement(10, _element[0] * _element[5] - _element[1] * _element[4]);

				result = result.multiply(1 / determinant);
			}
			else if (_column == 4)
			{
				//ONLY FOR HOMOGENEOUS MATRIX
				//ACTUALLY APPARENTLY DOES NOT WORK IF THERE IS A SCALE FACTOR BUT FUCK SCALING
				//http://content.gpwiki.org/index.php/MathGem:Fast_Matrix_Inversion

				result = *this;
				result.transpose();

				Vector3f newVector;
				newVector.setX(-(Vector3f(result.getElement(0), result.getElement(1), result.getElement(2)).dot(getTranslationVector())));
				newVector.setY(-(Vector3f(result.getElement(4), result.getElement(5), result.getElement(6)).dot(getTranslationVector())));
				newVector.setZ(-(Vector3f(result.getElement(8), result.getElement(9), result.getElement(10)).dot(getTranslationVector())));

				result.setElement(3, newVector.getX());
				result.setElement(7, newVector.getY());
				result.setElement(11, newVector.getZ());

				result.setElement(12, 0.0f);
				result.setElement(13, 0.0f);
				result.setElement(14, 0.0f);
				result.setElement(15, 1.0f);
			}
		}
		else

		{
			std::cerr << "ERROR: CANNOT CALCULATE DETERMANANT" << std::endl;
		}
	}
	else
	{
		std::cerr << "ERROR: CANNOT CALCULATE DETERMANANT" << std::endl;
	}

	return result;
}

float Matrix::getDeterminant()
{
	if (_column == _row)
	{
		if (_column == 2) //Not bad
		{
			return _element[0] * _element[5] - _element[1] * _element[4];
		}
		else if (_column == 3) //Ugh
		{
			return	  _element[0] * _element[5] * _element[10]
					+ _element[1] * _element[6] * _element[8]
					+ _element[2] * _element[4] * _element[9]
					- _element[2] * _element[5] * _element[8]
					- _element[1] * _element[4] * _element[10]
					- _element[0] * _element[6] * _element[9];
		}
		else if (_column == 4) //FML. I better not have made a mistake
		{
			return	  _element[0] * _element[5] * _element[10] * _element[15]
					+ _element[0] * _element[6] * _element[11] * _element[13]
					+ _element[0] * _element[7] * _element[9] * _element[14]

					+ _element[1] * _element[4] * _element[11] * _element[14]
					+ _element[1] * _element[6] * _element[8] * _element[15]
					+ _element[1] * _element[7] * _element[10] * _element[12]

					+ _element[2] * _element[4] * _element[9] * _element[15]
					+ _element[2] * _element[5] * _element[11] * _element[12]
					+ _element[2] * _element[7] * _element[8] * _element[13]

					+ _element[3] * _element[4] * _element[10] * _element[13]
					+ _element[3] * _element[5] * _element[8] * _element[14]
					+ _element[3] * _element[6] * _element[9] * _element[12]

					- _element[0] * _element[5] * _element[11] * _element[14]
					- _element[0] * _element[6] * _element[9] * _element[15]
					- _element[0] * _element[7] * _element[10] * _element[13]

					- _element[1] * _element[4] * _element[10] * _element[15]
					- _element[1] * _element[6] * _element[11] * _element[12]
					- _element[1] * _element[7] * _element[8] * _element[14]

					- _element[2] * _element[4] * _element[11] * _element[13]
					- _element[2] * _element[5] * _element[8] * _element[15]
					- _element[2] * _element[7] * _element[9] * _element[12]

					- _element[3] * _element[4] * _element[9] * _element[14]
					- _element[3] * _element[5] * _element[10] * _element[12]
					- _element[3] * _element[6] * _element[8] * _element[13];
		}
	}
	else
	{
		return -1;
	}
}

float Matrix::getTrace()
{
	float result;

	result = _element[0] + _element[5] + _element[10] + 1;

	return result;
}
//OpenGLs projection Matrix. Later need to take out the matrix paramater as it really makes no sense 
void Matrix::buildProjectionMatrix(double fieldOfView,
								  double asp,
								  double zNear, double zFar)
{
	double sine, cotangent, deltaZ;
	double radians =fieldOfView / 2.0 * FE_PI / 180.0;;

	deltaZ=zFar-zNear;
	sine = sin(radians);
	
	assert(deltaZ);
	assert(sine);
	assert(asp);
	cotangent = cos(radians) / sine;
	
	_element[0*4+0] = cotangent / asp;
	_element[0*4+1] = 0.0;
	_element[0*4+2] = 0.0;
	_element[0*4+3] = 0.0;

	_element[1*4+0] = 0.0;
	_element[1*4+1] = cotangent;
	_element[1*4+2] = 0.0;
	_element[1*4+3] = 0.0;
  
	_element[2*4+0] = 0.0;
	_element[2*4+1] = 0.0;
	_element[2*4+2] = -(zFar + zNear) / deltaZ;
	_element[2*4+3] = -2 * zNear * zFar / deltaZ;

	_element[3*4+0] = 0.0;
	_element[3*4+1] = 0.0;
	_element[3*4+2] = -1;
	_element[3*4+3] = 0;

}

//glu's LookAtMatrix
void Matrix::buildLookAtMatrix(double eyex, double eyey, double eyez,
                              double centerx, double centery, double centerz,
                              double upx, double upy, double upz
                              )
{
	Vector3f x, y, z;
	double mag;

	z.set(eyex - centerx, eyey-centery, eyez - centerz);
	z.normalize();

	y.set(upx, upy, upz);

	x = y.cross(z);

	y = z.cross(x);

	x.normalize();
	y.normalize();
	//float ele []=(x, y, z)
	//viewMatrix.set(x., y, z)
	
	_element[0*4+0] = x.getX();  _element[0*4+1] = x.getY();
	
	_element[0*4+2] = x.getZ();  _element[0*4+3] = -x.getX()*eyex + -x.getY()*eyey + -x.getZ()*eyez;

	_element[1*4+0] = y.getX();  _element[1*4+1] = y.getY();
	_element[1*4+2] = y.getZ();  _element[1*4+3] = -y.getX()*eyex + -y.getY()*eyey + -y.getZ()*eyez;
	
	_element[2*4+0] = z.getX();  _element[2*4+1] = z.getY();
	_element[2*4+2] = z.getZ();  _element[2*4+3] = -z.getX()*eyex + -z.getY()*eyey + -z.getZ()*eyez;
	
	_element[3*4+0] = 0.0;  _element[3*4+1] = 0.0; _element[3*4+2] = 0.0; _element[3*4+3] = 1.0;

}

void Matrix::buildLookAtMatrixForDummies(double eyex, double eyey, double eyez,
                              double centerx, double centery, double centerz,
                              double upx, double upy, double upz)
{
	 double x[3], y[3], z[3], mag;

  /* Difference eye and center vectors to make Z vector. */
  z[0] = eyex - centerx;
  z[1] = eyey - centery;
  z[2] = eyez - centerz;
  /* Normalize Z. */
  mag = sqrt(z[0]*z[0] + z[1]*z[1] + z[2]*z[2]);
  if (mag) {
    z[0] /= mag;
    z[1] /= mag;
    z[2] /= mag;
  }

  /* Up vector makes Y vector. */
  y[0] = upx;
  y[1] = upy;
  y[2] = upz;

  /* X vector = Y cross Z. */
  x[0] =  y[1]*z[2] - y[2]*z[1];
  x[1] = -y[0]*z[2] + y[2]*z[0];
  x[2] =  y[0]*z[1] - y[1]*z[0];

  /* Recompute Y = Z cross X. */
  y[0] =  z[1]*x[2] - z[2]*x[1];
  y[1] = -z[0]*x[2] + z[2]*x[0];
  y[2] =  z[0]*x[1] - z[1]*x[0];

  /* Normalize X. */
  mag = sqrt(x[0]*x[0] + x[1]*x[1] + x[2]*x[2]);
  if (mag) {
    x[0] /= mag;
    x[1] /= mag;
    x[2] /= mag;
  }

  /* Normalize Y. */
  mag = sqrt(y[0]*y[0] + y[1]*y[1] + y[2]*y[2]);
  if (mag) {
    y[0] /= mag;
    y[1] /= mag;
    y[2] /= mag;
  }

  /* Build resulting view matrix. */
  _element[0*4+0] = x[0];  _element[0*4+1] = x[1];
  _element[0*4+2] = x[2];  _element[0*4+3] = -x[0]*eyex + -x[1]*eyey + -x[2]*eyez;

  _element[1*4+0] = y[0];  _element[1*4+1] = y[1];
  _element[1*4+2] = y[2];  _element[1*4+3] = -y[0]*eyex + -y[1]*eyey + -y[2]*eyez;

  _element[2*4+0] = z[0];  _element[2*4+1] = z[1];
  _element[2*4+2] = z[2];  _element[2*4+3] = -z[0]*eyex + -z[1]*eyey + -z[2]*eyez;

  _element[3*4+0] = 0.0;   _element[3*4+1] = 0.0;  _element[3*4+2] = 0.0;  _element[3*4+3] = 1.0;
}
	void Matrix::makeRotateMatrix(float angle, Vector3f axis) 
	{
		float radians, sine, cosine, ab, bc, ca, tx, ty, tz;
		
		axis.normalize();

		radians = mDegToRad(angle);
		sine = sin (radians);
		cosine = cos(radians);

		ab = axis.getX()*axis.getY()*(1-cosine);
		bc = axis.getY()*axis.getZ()*(1-cosine);
		ca = axis.getZ()*axis.getX()*(1-cosine);

		tx= axis.getX()*axis.getX();
		ty= axis.getX()*axis.getY();
		tz= axis.getX()*axis.getZ();

		
		_element[0]  = tx + cosine * (1 - tx);
		_element[1]  = ab + axis.getZ() * sine;
		_element[2]  = ca - axis.getY() * sine;
		_element[3]  = 0.0f;
		_element[4]  = ab - axis.getZ() * sine;
		_element[5]  = ty + cosine * (1 - ty);
		_element[6]  = bc + axis.getX() * sine;
		_element[7]  = 0.0f;
		_element[8]  = ca + axis.getY() * sine;
		_element[9]  = bc - axis.getX() * sine;
		_element[10] = tz + cosine * (1 - tz);
		_element[11] = 0;
		_element[12] = 0;
		_element[13] = 0;
		_element[14] = 0;
		_element[15] = 1;

	}

	void Matrix::makeRotateMatrixForDummies(float angle,
                            float ax, float ay, float az)
	{  

  float radians, sine, cosine, ab, bc, ca, tx, ty, tz;
  float axis[3];
  float mag;

  axis[0] = ax;
  axis[1] = ay;
  axis[2] = az;
  mag = sqrt(axis[0]*axis[0] + axis[1]*axis[1] + axis[2]*axis[2]);
  if (mag) {
    axis[0] /= mag;
    axis[1] /= mag;
    axis[2] /= mag;
  }

  radians = angle * FE_PI / 180.0;
  sine = sin(radians);
  cosine = cos(radians);
  ab = axis[0] * axis[1] * (1 - cosine);
  bc = axis[1] * axis[2] * (1 - cosine);
  ca = axis[2] * axis[0] * (1 - cosine);
  tx = axis[0] * axis[0];
  ty = axis[1] * axis[1];
  tz = axis[2] * axis[2];

  _element[0]  = tx + cosine * (1 - tx);
  _element[1]  = ab + axis[2] * sine;
  _element[2]  = ca - axis[1] * sine;
  _element[3]  = 0.0f;
  _element[4]  = ab - axis[2] * sine;
  _element[5]  = ty + cosine * (1 - ty);
  _element[6]  = bc + axis[0] * sine;
  _element[7]  = 0.0f;
  _element[8]  = ca + axis[1] * sine;
  _element[9]  = bc - axis[0] * sine;
  _element[10] = tz + cosine * (1 - tz);
  _element[11] = 0;
  _element[12] = 0;
  _element[13] = 0;
  _element[14] = 0;
  _element[15] = 1;
	}

void Matrix::makeTranslateMatrix(Vector3f vec)
{
	//m.set(		1.0,	0,		0,		vec.getX(),
	//			0,		1,		0,		 vec.getY(),	
	//			0,		0,		1,		 vec.getZ(), 
	//			0,		0,		0,		1);
	_element[0]  = 1;  _element[1]  = 0;  _element[2]  = 0;  _element[3]  = vec.getX();
	_element[4]  = 0;  _element[5]  = 1;  _element[6]  = 0;  _element[7]  = vec.getY();
	_element[8]  = 0;  _element[9]  = 0;  _element[10] = 1;  _element[11] = vec.getZ();
	_element[12] = 0;  _element[13] = 0;  _element[14] = 0;  _element[15] = 1;
}
// for shaders
void Matrix::multMatrix(Matrix dst, const Matrix src1, const Matrix src2)
{
	Matrix tmp;
	int i, j;

	  for (i=0; i<4; i++) {
    for (j=0; j<4; j++) {
      tmp._element[i*4+j] = src1._element[i*4+0] * src2._element[0*4+j] +
                   src1._element[i*4+1] * src2._element[1*4+j] +
                   src1._element[i*4+2] * src2._element[2*4+j] +
                   src1._element[i*4+3] * src2._element[3*4+j];
    }
  }
  /* Copy result to dst (so dst can also be src1 or src2). */
  for (i=0; i<16; i++)
    dst._element[i] = tmp._element[i];
}
//for shaders
Matrix Matrix::modelViewProjection(Matrix modelView)

{
	 modelView.transpose();
	 return modelView;
}

void Matrix::setIdentity()
{
	_element[0] = 1.0f;
	_element[5] = 1.0f;
	_element[10] = 1.0f;
	_element[15] = 1.0f;
}

void Matrix::transpose()
{
	float saved;

	if (_column == 2)
	{
		saved = _element[1];
		_element[1] = _element[4];
		_element[4] = saved;
	}
	else if (_column == 3)
	{
		saved = _element[1];
		_element[1] = _element[4];
		_element[4] = saved;

		saved = _element[2];
		_element[2] = _element[8];
		_element[8] = saved;

		saved = _element[6];
		_element[6] = _element[9];
		_element[9] = saved;
	}
	else if (_column == 4)
	{
		saved = _element[1];
		_element[1] = _element[4];
		_element[4] = saved;

		saved = _element[2];
		_element[2] = _element[8];
		_element[8] = saved;

		saved = _element[3];
		_element[3] = _element[12];
		_element[12] = saved;

		saved = _element[6];
		_element[6] = _element[9];
		_element[9] = saved;

		saved = _element[7];
		_element[7] = _element[13];
		_element[13] = saved;

		saved = _element[11];
		_element[11] = _element[14];
		_element[14] = saved;
	}
}

void Matrix::getUniformLocation(unsigned int program, const char *Mat)
{

		*_element = glGetUniformLocation(program, Mat);
		//glUniformMatrix
/*void Matrix::clean() //Gets rid of really ugly rotation numbers by clamping/rounding
{
	for (unsigned int i = 0; i < 16; ++i)
	{
		if (_element[i] >= -0.001 && _element[i] <= 0.001)
		{
			_element[i] = 0.0f;
		}
		else if (_element[i] >= 0.999 && _element[i] <= 1.001)
		{
			_element[i] = 1.0f;
		}
		else if (_element[i] <= -0.999 && _element[i] >= -1.001)
		{
			_element[i] = -1.0f;
		}
	}*/
}

void Matrix::FE_LOAD_MATRIX(bool transpose)
{
	Matrix *m = this;
	
	if (transpose)
	{
		m->transpose();
		glLoadMatrixf(m->_element);
	}

		
	glLoadMatrixf(_element);
}

void Matrix::print()
{
	std::cout << _element[0] << "	" << _element[1] << "	" << _element[2] << "	" << _element[3] << std::endl;
	std::cout << _element[4] << "	" << _element[5] << "	" << _element[6] << "	" << _element[7] << std::endl;
	std::cout << _element[8] << "	" << _element[9] << "	" << _element[10] << "	" << _element[11] << std::endl;
	std::cout << _element[12] << "	" << _element[13] << "	" << _element[14] << "	" << _element[15] << std::endl;
}