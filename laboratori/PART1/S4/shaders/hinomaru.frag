#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

bool inCercle(vec2 centre, float radi, vec2 p) {
	return (distance(centre, p) <= radi);
}

void main()
{
	vec2 centre = vec2(0.5, 0.5);
	float radi = 0.2;
	fragColor = vec4(1);
	// HINOMARU BIS
	float d = length(vtexCoord - centre);
	float w = length(vec2(dFdx(d), dFdy(d)));
	fragColor = vec4(1, vec2(smoothstep(radi - w, radi + w, d)), 0);
	// HINOMARU SIN ANTI-ALIASING
	//if (inCercle(centre, radi, vtexCoord)) fragColor = vec4(1, 0, 0, 0);
    
}
