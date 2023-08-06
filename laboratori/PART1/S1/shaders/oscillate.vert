#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;
const float PI = 3.141592;
uniform float periode = 2*PI;
uniform float time;
uniform vec3 boundingBoxMin;			//cantonada de la capsa englobant
uniform vec3 boundingBoxMax;			//cantonada de la capsa englobant
uniform bool eyespace;

void main()
{
	float amplitude;
	vec3 posMin = vec3(boundingBoxMin.x, boundingBoxMin.y, boundingBoxMin.z);
	vec3 posMax = vec3(boundingBoxMax.x, boundingBoxMax.y, boundingBoxMax.z);
	float diagonal = distance(posMin, posMax);
	float r = diagonal/2;
	float frequencia = 1/periode;
	if (eyespace == true) {
		vec4 eye = modelViewMatrix * vec4(vertex, 1.0);
		amplitude = (r/10)*eye.y;
	}	
	else if (eyespace == false) {
		amplitude = (r/10)*vertex.y;	
	}	
	float sinus = amplitude * sin(2 * PI * frequencia * time);
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0);
    vtexCoord = texCoord;
	vec3 v = vec3(vertex.x + (sinus*normal.x), vertex.y + (sinus*normal.y), vertex.z + (sinus*normal.z));
    gl_Position = modelViewProjectionMatrix * vec4(v, 1.0);
}
