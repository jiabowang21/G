#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;

const vec4 RED=vec4(1, 0, 0, 1);
const vec4 YELLOW=vec4(1, 1, 0, 1);

void main()
{
	float a = 1.0/9;
	float f = fract(vtexCoord.s);
	if (f >= 0 && f < a) fragColor = YELLOW;
	else if (f >= float(2*a) && f < float(3*a)) fragColor = YELLOW;
	else if (f >= 4*a && f < 5*a) fragColor = YELLOW;
	else if (f >= 6*a && f < 7*a) fragColor = YELLOW;
	else if (f >= 8*a && f < 9*a) fragColor = YELLOW;
    else fragColor = RED;
}
