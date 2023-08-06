#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

const vec4 B = vec4(1);
const vec4 N = vec4(0);
const vec4 G = vec4(0.8);
const vec4 P = vec4(1.0, 0.8, 0.6, 1.0);
uniform int mode = 2;

bool isInCircle(vec2 centre, float rad, vec2 point) {
	return distance(centre, point) <= rad;
}

void mode0() {
	if (isInCircle(vec2(0.5, 0.4), 0.33, vtexCoord)) fragColor = N;
	if (isInCircle(vec2(0.2, 0.8), 0.2, vtexCoord)) fragColor = N;
	if (isInCircle(vec2(0.8, 0.8), 0.2, vtexCoord)) fragColor = N;
}

void mode1() {
	if (isInCircle(vec2(0.9, 0.4), 0.25, vec2(vtexCoord.x*2, vtexCoord.y))) fragColor = P;
	if (isInCircle(vec2(1.1, 0.4), 0.25, vec2(vtexCoord.x*2, vtexCoord.y))) fragColor = P;
	if (isInCircle(vec2(0.5, 0.55), 0.28, vec2(vtexCoord.x, vtexCoord.y*2))) fragColor = P;
}

void mode2() {
	if (isInCircle(vec2(0.9, 0.48), 0.13, vec2(vtexCoord.x*2, vtexCoord.y))) fragColor = B;
	if (isInCircle(vec2(1.1, 0.48), 0.13, vec2(vtexCoord.x*2, vtexCoord.y))) fragColor = B;
	if (isInCircle(vec2(0.9, 0.43), 0.07, vec2(vtexCoord.x*2, vtexCoord.y))) fragColor = N;
	if (isInCircle(vec2(1.1, 0.43), 0.07, vec2(vtexCoord.x*2, vtexCoord.y))) fragColor = N;
}

void main()
{
    fragColor = G;
	if (mode == 0) {
		mode0();
	}
	else if (mode == 1) {
		mode0();
		mode1();
	}
	else if (mode == 2) {
		mode0();
		mode1();
		mode2();
	}
}
