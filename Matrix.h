#pragma once

//Currently unused since anflasnfosanfonfsaasnf hard coding inverses

#include "Vector3f.h"
#include "Conversions.h"
#include<assert.h>
#include <math.h>
#include <iostream>

#define NG_COLUMN 0
#define NG_ROW 1

class Matrix
{
public:
	Matrix();
	Matrix(Vector3f vector);
	Matrix(Vector3f rotate, Vector3f translation, Vector3f scale);
	~Matrix();

	void makeHomogenous(Vector3f rotate, Vector3f translation, Vector3f scale);
	void makeHomogenousV2(Matrix rotationMatrix, Vector3f translation, Vector3f scale);

	void buildProjectionMatrix(double fieldOfView,
							   double aspectRation,
							   double zMin, double zMax);
	static void buildPerspectiveMatrix( double fieldOfView, 
										double asp, 
										double zNear, double zFar);



	void buildLookAtMatrix(double eyex, double eyey, double eyez,
                              double centerx, double centery, double centerz,
                              double upx, double upy, double upz
                              );
	void buildLookAtMatrixForDummies(double eyex, double eyey, double eyez,
                              double centerx, double centery, double centerz,
                              double upx, double upy, double upz);
	

	void makeRotateMatrix(float angle,
                            Vector3f axis);
	void makeRotateMatrixForDummies(float angle,
                            float ax, float ay, float az);

	void makeTranslateMatrix(Vector3f vec);

	void multMatrix(Matrix dst, const Matrix src1, const Matrix src2);

	Matrix modelViewProjection(Matrix modelView);


	void setSize(unsigned int column, unsigned int row);
	unsigned int getSize(unsigned int element); //0 for column, 1 for row

	void setElement(unsigned int index, float value);
	float getElement(unsigned int index);

	void set(float* elements);
	float* get();

	Matrix getRotationMatrix();
	Vector3f getTranslationVector();
	Vector3f getColVector(int col);
	Vector3f getRowVector(int row);

	float* getRow(unsigned int row);

	Matrix add(Matrix &otherMatrix);
	Matrix subtract(Matrix &otherMatrix);
	Matrix multiply(Matrix &otherMatrix);
	Vector3f multiply(Vector3f &vector);
	Matrix multiply(float scalar);

	void getUniformLocation(unsigned int program, const char *Mat);

	Matrix getInverse();

	float getDeterminant();
	float getTrace();

	void setIdentity();
	void transpose();
	//void clean();
	void FE_LOAD_MATRIX(bool transpose);

	void print();


private:
	float _element[16];

	unsigned int _column, _row;
};
struct shaderMatrix
{
	float m[16];
};