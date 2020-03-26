#pragma once


#include <iostream>

class Conversions;

class Vector3f
{
public:
	Vector3f();
	Vector3f(float newX, float newY, float newZ);
	~Vector3f(void);

	inline float getX();
	inline float getY();
	inline float getZ();

	inline void set(float x, float y, float z);
	inline void setX(float newX);
	inline void setY(float newY);
	inline void setZ(float newZ);

	inline float Magnitude();
	inline float Distance(Vector3f &otherVec);
	Vector3f Angle(Vector3f &otherVec);
	inline Vector3f Projection (Vector3f &otherVec);
	inline float ProjectionLength (Vector3f &otherVec);

	inline void normalize();

	inline Vector3f subtract(Vector3f &otherVec);
	inline Vector3f add(Vector3f &otherVec);
	inline Vector3f multiply(Vector3f &otherVec);
	inline Vector3f scalarMultiply(float num);

	inline Vector3f& operator +=(Vector3f otherVec);
	inline Vector3f& operator -=(Vector3f otherVec);
	inline Vector3f& operator *=(float scalar);

	inline const Vector3f& operator =(Vector3f otherVec);
	inline const Vector3f& operator +(Vector3f otherVec);
	inline const Vector3f& operator -(Vector3f otherVec);
	inline const Vector3f& operator *(float scalar);

	inline float dot(Vector3f &otherVec);
	inline Vector3f cross(Vector3f &otherVec);

	inline Vector3f lerp(Vector3f &otherVec, float &t);

	inline void print();

protected:
	float _x, _y, _z;

};
#include "Vector3f.inl"

