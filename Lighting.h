#pragma once
#include "Vector3f.h"
class Lighting
{
public:
	Lighting(void);
	~Lighting(void);
	void setUniformLocations(unsigned int program);
	void setBrassMaterial(unsigned int shader);

private:
	int _emmisive;
	int _ambient;
	int _diffuse;
	int _specular;
	int _shininess;
};