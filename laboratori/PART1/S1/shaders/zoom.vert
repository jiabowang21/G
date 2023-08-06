#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelViewProjectionMatrixInverse;
uniform mat3 normalMatrix;
uniform float time;

void main()
{
	float escala = 0.5 + abs(sin(time));
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0) * N.z;
    vtexCoord = texCoord;
    vec4 v = modelViewMatrix * vec4(vertex, 1.0);
	/*v.x = v.x/-v.z;
	v.y = v.y/-v.z;
	v.z = v.z/-v.z;*/
	float y = (v.y / -v.z); 					//divisió perspectiva
	y = y*escala*-v.z;
	float x = (v.x / -v.z);
	x = x*escala*-v.z;
	gl_Position = projectionMatrix * vec4(x, y, v.z, 1.0);
}
