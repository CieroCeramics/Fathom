float Vector3f::getX()
{
	return _x;
}

float Vector3f::getY()
{
	return _y;
}

float Vector3f::getZ()
{
	return _z;
}

void Vector3f::set(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
}

void Vector3f::setX(float newX)
{
	_x = newX;
}

void Vector3f::setY(float newY)
{
	_y = newY;
}

void Vector3f::setZ(float newZ)
{
	_z = newZ;
}

float Vector3f::Magnitude()
{
	return sqrt(_x * _x + _y * _y + _z * _z);
}

float Vector3f::Distance(Vector3f &otherVec)
{
	return subtract(otherVec).Magnitude();
}

Vector3f Vector3f::Projection(Vector3f &otherVec)
{
	return otherVec.scalarMultiply(this ->dot(otherVec) / otherVec.Magnitude() * otherVec.Magnitude());
}

float Vector3f::ProjectionLength(Vector3f &otherVec)
{
	return this ->subtract(otherVec.scalarMultiply(this ->dot(otherVec) / (otherVec.Magnitude() * otherVec.Magnitude()))).Magnitude();
}

void Vector3f::normalize()
{
	if (Magnitude() != 0)
	{
		float normalizationFactor = 1 / Magnitude();

		//this ->scalarMultiply(normalizationFactor);

		_x *= normalizationFactor;
		_y *= normalizationFactor;
		_z *= normalizationFactor;
	}
}

Vector3f Vector3f::subtract(Vector3f &otherVec)
{
	Vector3f result = Vector3f(_x - otherVec.getX(), _y - otherVec.getY(), _z - otherVec.getZ());

	return result;
}

Vector3f Vector3f::add(Vector3f &otherVec)
{
	Vector3f result = Vector3f(_x + otherVec.getX(), _y + otherVec.getY(), _z + otherVec.getZ());

	return result;
}

Vector3f Vector3f::multiply(Vector3f &otherVec)
{
	Vector3f result = Vector3f(_x * otherVec.getX(), _y * otherVec.getY(), _z * otherVec.getZ());

	return result;
}

Vector3f Vector3f::scalarMultiply(float num)
{
	Vector3f result = Vector3f(_x * num, _y * num, _z * num);

	return result;
}

Vector3f& Vector3f::operator +=(Vector3f otherVec)
{
	_x += otherVec.getX();
	_y += otherVec.getY();
	_z += otherVec.getZ();

	return *this;
}

Vector3f& Vector3f::operator -=(Vector3f otherVec)
{
	_x -= otherVec.getX();
	_y -= otherVec.getY();
	_z -= otherVec.getZ();

	return *this;
}

Vector3f& Vector3f::operator *=(float scalar)
{
	_x *= scalar;
	_y *= scalar;
	_z *= scalar;

	return *this;
}

const Vector3f& Vector3f::operator =(Vector3f otherVec)
{
	_x = otherVec.getX();
	_y = otherVec.getY();
	_z = otherVec.getZ();

	return *this;
}

const Vector3f& Vector3f::operator +(Vector3f otherVec)
{
	return Vector3f(_x + otherVec.getX(), _y + otherVec.getY(), _z + otherVec.getZ());
}

const Vector3f& Vector3f::operator -(Vector3f otherVec)
{
	return Vector3f(_x - otherVec.getX(), _y - otherVec.getY(), _z - otherVec.getZ());
}

const Vector3f& Vector3f::operator *(float scalar)
{
	return Vector3f(_x * scalar, _y * scalar, _z * scalar);
}

float Vector3f::dot(Vector3f &otherVec)
{
	return (_x * otherVec.getX() + _y * otherVec.getY() + _z * otherVec.getZ());
}

Vector3f Vector3f::cross(Vector3f &otherVec)
{
	Vector3f result = Vector3f(_y * otherVec.getZ() - _z * otherVec.getY(), 
							   _z * otherVec.getX() - _x * otherVec.getZ(), 
							   _x * otherVec.getY() - _y * otherVec.getX());

	return result;
}

Vector3f Vector3f::lerp(Vector3f &otherVec, float &t)
{
	Vector3f result = Vector3f((1 - t) * _x + t * otherVec.getX(),
							   (1 - t) * _y + t * otherVec.getY(),
							   (1 - t) * _z + t * otherVec.getZ());

	return result;
}

void Vector3f::print()
{
	std::cout << _x << ", " << _y << ", " << _z << std::endl;
}