#version 330

layout (location = 0) in vec3 position;
layout (location = 2) in vec3 normal;
layout (location = 8) in vec2 texcoord;

out VertexData {
	vec2 texcoord;
	vec3 normalEye;
	vec3 objectPos;
	vec3 positionEye;
	vec4 mvp;
	}data;

	uniform mat4 modelViewProj;
	uniform vec3 lightPosition;
	uniform vec3 eyePosition;
void main()
{
	
	vec4 positionEye = modelViewProj * vec4(position, 1);
	gl_Position = positionEye;
	data.positionEye = positionEye.xyz;
	//data.mvp= modelViewProj;
	data.objectPos=position.xyz;
	data.normalEye = normal;
	data.texcoord = texcoord.st;




}

