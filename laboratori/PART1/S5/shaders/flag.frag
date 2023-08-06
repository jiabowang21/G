#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;

const vec4 G = vec4(1, 0.75, 0, 1);
const vec4 W = vec4(1.);
float ar = 3./4.;

bool isInCircle(vec2 centre, float rad, vec2 point) {
	return distance(centre, point) <= rad;
}

void main() {
    fragColor = G;
	float radi = 0.24;
	vec2 centro = vec2(0.28, 0.5*ar);
	float radi2 = 0.22;
	vec2 centro2 = vec2(0.38, 0.5*ar);
	vec2 coord = vtexCoord;
	coord.y *= ar;
	if (vtexCoord.x > 0.6 && vtexCoord.x < 0.85 && vtexCoord.y > 0.3 && vtexCoord.y < 0.75)
		fragColor = W;
	if (isInCircle(centro, radi, coord)) 
		if (!isInCircle(centro2, radi2, coord)) fragColor = W; 
}

/*
vec4 blueish =  vec4(35., 84., 127., 255)/255;
vec4 white = vec4(1.);

float ar = 3./4.;


bool isInCircle(vec2 centre, float rad, vec2 point) {
	return distance(centre, point) <= rad;
}

bool isInRect(vec2 m, vec2 M, vec2 point) {
	return (point.x >= m.x && point.x <= M.x) && (point.y >= m.y && point.y <= M.y);
}

void main()
{
	vec2 coord = vtexCoord;
	coord.y *= ar;
    fragColor = blueish;
    if (isInCircle( vec2(.25,.5*ar), 0.15, coord))
    	fragColor = white;
	if (isInCircle( vec2(.7,.5*ar), 0.25, coord))
		if (!isInCircle( vec2(.55,.5*ar), 0.25, coord))
			fragColor = white;
}
*/
