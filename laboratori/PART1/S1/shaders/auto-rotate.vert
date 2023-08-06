#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform float speed = 1;
uniform float time;

void main()
{
	float vel = time * speed;
    vec3 N = normalize(normalMatrix * normal);
	mat3 m = mat3(vec3(cos(vel), 0, -sin(vel)), vec3(0, 1, 0), vec3(sin(vel), 0, cos(vel))); //rotacio y
	//mat3 m = mat3(vec3(1, 0, 0), vec3(0, cos(vel), sin(vel)), vec3(0, -sin(vel), cos(vel))); //rotacio x
	//mat3 m = mat3(vec3(cos(vel), sin(vel), 0), vec3(-sin(vel), cos(vel), 0), vec3(0, 0, 1)); //rotacio z
	vec3 vec = m * vertex;
	frontColor = vec4(color,1.0) * N.z;    
	vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(vec, 1.0);
}
