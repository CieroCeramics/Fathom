#version 330 core

//out vec4 fragColour;

in VertexData{
 vec2 texcoord;
 vec3 normalEye;
 vec3 objectPos;
vec3 positionEye;
vec4 mvp;
}data;

uniform vec3 globalAmbient;
uniform vec3 lightColour;
uniform vec3 lightPosition;
uniform vec3 eyePosition;
//uniform vec3 Ke;
uniform vec3 Ka;
uniform vec3 Kd; 
uniform vec3 Ks;
uniform float shininess;

uniform sampler2D colourTex;

layout (location = 0) out vec4 fragColour;


void main()
{
	//vec3 lightPos = vec3(1.0,8.0,5.0);
	 
	vec3 P = data.positionEye;
	vec3 N = normalize(data.normalEye);
	

	//ambi
	
	vec3 ambient = Ka * globalAmbient;

	//diff

	vec3 L = normalize(lightPosition - P);

	float diffuseCoef = max(dot(L,N),0.0);
	vec3 diffuse = Kd * lightColour * diffuseCoef;

	//Spec
	vec3 V = normalize(eyePosition-P);
	vec3 H = normalize(L + V);
	
	float specularCoef = pow(max(dot( H,N), 0), shininess);
	 if (diffuseCoef <= 0) specularCoef = 0;

	 vec3 specular = Ks * lightColour * specularCoef;

	 // colourTex = ambient + diffuse + specular;
	 vec3 colour = ambient + diffuse + specular;
	 
	fragColour = vec4 (colour, 1);




		// Rimlight Shader
const float rimStart = 0.5f;
const float rimEnd = 0.3f;
const float rimMultiplier = 1.0f;
vec3  rimColor = vec3(1.0f, 1.0f, 1.0f);
 
float NormalToCam = 1.0 - dot(normalize(N), normalize(P - data.objectPos));
float rim = smoothstep(rimStart, rimEnd, NormalToCam) * rimMultiplier;
 
 //fragColour.rgb += (rimColor * rim);

	 fragColour = vec4(diffuse,  1);

}