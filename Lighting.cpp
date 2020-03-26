#include "Lighting.h"
#include "Include.h"

Lighting::Lighting()
{
	/*for (unsigned int i= 0; i<3; ++i)
	{

	_diffuse = 0;
	_ambient = 0;
	_specular = 0;
	}
	_emmisive = 0;*/


}
int terms = 3;

Lighting::~Lighting(void)
{
}

void Lighting::setUniformLocations(unsigned int program)
{
	_ambient = glGetUniformLocation(program,"Ka" );
	  _diffuse = glGetUniformLocation(program,"Kd" );
	  _specular = glGetUniformLocation(program,"Ks" );
	  _shininess = glGetUniformLocation(program, "shininess");
}


void Lighting::setBrassMaterial(unsigned int program)
{
	 float brassEmmisive =0.0;
	 float  brassAmbient[3] = {0.33, 0.22, 0.03};
	 float brassDiffuse[3]  = {0.78, 0.57, 0.11};
	 float brassSpecular[3]=   {0.99, 0.91, 0.81};
       float brassShininess =  27.8;

	   glUniform3f(_ambient, brassAmbient[0],brassAmbient[1],brassAmbient[2] );
	   glUniform3f(_diffuse, brassDiffuse[0],brassDiffuse[1],brassDiffuse[2]);
	   glUniform3f(_specular,brassSpecular[0],brassSpecular[1],brassSpecular[2]);
	   glUniform1f(_shininess, brassShininess);
	
}
