#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;

uniform float time;

bool inCircle(vec2 p, vec2 c, float r) {
	return (distance(p, c) <= r);
}

bool inRect(vec2 p, vec2 m, vec2 M) {
	return (p.x >= m.x && p.x <= M.x) && (p.y >= m.y && p.y <= M.y); 
}

void main()
{
	float R = 3 + sin(time);
	float r = 2;   
	vec2 p = 10 * vtexCoord - vec2(5);
    fragColor = vec4(0);
	if (inCircle(p, vec2(0, -1), R) && !inCircle(p, vec2(0, -1), r) && p.y <= -1) {
		fragColor = vec4(1);
	}
	if (inRect(p, vec2(2, -1), vec2(R, 4))) fragColor = vec4(1);
}

