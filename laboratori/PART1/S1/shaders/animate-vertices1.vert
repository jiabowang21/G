#version 330 core

layout (location = 0) in vec3 vertex;			//object space
layout (location = 1) in vec3 normal;			//object space
layout (location = 2) in vec3 color;			//colors [0, 1]
layout (location = 3) in vec2 texCoord;			//coordenades de textura (s,t)

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;			//object -> clip
uniform mat3 normalMatrix;						//object -> eye
uniform float amplitude = 0.1;
uniform float freq = 1;
uniform float time;
const float PI = 3.141592;

void main()
{
	float sinus = amplitude * sin(2 * PI * freq * time);
    vec3 N = normalize(normalMatrix * normal);	//transformar i normalitzar normal
	vec3 v = vec3(vertex.x + (sinus*normal.x), vertex.y + (sinus*normal.y), vertex.z + (sinus*normal.z));
    frontColor = vec4(N.z);
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(v, 1.0);	//clip space
}
