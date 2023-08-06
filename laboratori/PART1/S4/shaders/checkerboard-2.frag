#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;
uniform float n = 8; 

const vec4 GRIS = vec4(0.8);

void main()
{
	if (mod(vtexCoord.x, 2/n) >= 1/n && mod(vtexCoord.y, 2/n) <= 1/n) fragColor = vec4(0);

	else if (mod(vtexCoord.x, 2/n) < 1/n && mod(vtexCoord.y, 2/n) > 1/n) fragColor = vec4(0);

	
    else fragColor = GRIS;
}

