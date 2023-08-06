#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform vec4 RED = vec4(1, 0, 0, 1);
uniform vec4 YELLOW = vec4(1, 1, 0, 1);
uniform vec4 GREEN = vec4(0, 1, 0, 1);
uniform vec4 CYAN = vec4(0, 1, 1, 1);
uniform vec4 BLUE = vec4(0, 0, 1, 1);

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);

	float yMin = -1.0;
	float yMax = 1.0;
	float y = (gl_Position.y / gl_Position.w); 					//divisió perspectiva
	float yi = 4*(y - yMin) / (yMax - yMin);					//proporció
	if (yi == 0) frontColor = RED;
    else if (yi < 1) frontColor = mix(RED, YELLOW, fract(yi)); 
    else if (yi < 2) frontColor = mix(YELLOW, GREEN, fract(yi));
    else if (yi < 3) frontColor = mix(GREEN, CYAN, fract(yi));
    else if (yi < 4) frontColor = mix(CYAN, BLUE, fract(yi));
    else if (yi == 4) frontColor = BLUE;
}

/*
	RED (0)			Min
					gradient 1 (RED - YELLOW)			0 < y < 0.25     	0 < y < 1
	YELLOW (1)
					gradient 2 (YELLOW - GREEN)			0.25 < y < 0.5		1 < y < 2 
	GREEN (2)
					gradient 3 (GREEN - CYAN)			0.5 < y < 0.75		2 < y < 3
	CYAN (3)
					gradient 4 (CYAN - BLUE)			0.75 < y < 1		3 < y < 4
	BLUE (4)		Max
*/
