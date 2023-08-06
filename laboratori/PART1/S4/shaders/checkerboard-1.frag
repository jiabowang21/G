#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;

const vec4 GRIS = vec4(0.8);

void main()
{
	if (mod(vtexCoord.x, 0.25) >= 0.125 && mod(vtexCoord.y, 0.25) <= 0.125) fragColor = vec4(0);

	else if (mod(vtexCoord.x, 0.25) < 0.125 && mod(vtexCoord.y, 0.25) > 0.125) fragColor = vec4(0);

	
    else fragColor = GRIS;
}

// 8 x 8 0.125 0.25 0.375 0.5 
