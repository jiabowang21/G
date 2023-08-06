#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;
uniform sampler2D colorMap;


float map (float a, float b, float c, float d, float x) {
	return (x - a) / (b - a) * (d - c) + c;
}

void printNumber (float numero, float position) {
	if (vtexCoord.x >= position && vtexCoord.x <= (position + float(1./6))) {
		float s = map (position, position + float(1./6), numero/10, numero/10 + float(1./10), vtexCoord.x);
		vec4 text = texture(colorMap, vec2(s, vtexCoord.y));
		if (text.a < 0.5) discard;
		else fragColor = text * vec4(0, 0, 1, 0);
	}		
}

void main() {
	printNumber (0., float(0./6));
	printNumber (7, float(1./6));
	printNumber (3, float(2./6));
	printNumber (0, float(3./6));
	printNumber (3, float(4./6));
	printNumber (4, float(5./6));	
}

/*void main()
{
	vec4 text;
	if (vtexCoord.x <= float(1./6) && vtexCoord.x >= 0) {
		float s = map (0.0, float(1./6), 0.0, float(1./10), vtexCoord.x);
		text = texture(colorMap, vec2(s, vtexCoord.y)); 
	}
	else if (vtexCoord.x <= float(2./6) && vtexCoord.x >= float(1./6)) {
		float s = map (float(1./6), float(2./6), float(7./10), float(8./10), vtexCoord.x);
		text = texture(colorMap, vec2(s, vtexCoord.y));    
	}
	else if (vtexCoord.x <= float(3./6) && vtexCoord.x >= float(2./6)) {
		float s = map (float(2./6), float(3./6), float(3./10), float(4./10), vtexCoord.x);
		text = texture(colorMap, vec2(s, vtexCoord.y));    
	}
	else if (vtexCoord.x <= float(4./6) && vtexCoord.x >= float(3./6)) {
		float s = map (float(3./6), float(4./6), float(0./10), float(1./10), vtexCoord.x);
		text = texture(colorMap, vec2(s, vtexCoord.y));    
	}
	else if (vtexCoord.x <= float(5./6) && vtexCoord.x >= float(4./6)) {
		float s = map (float(4./6), float(5./6), float(3./10), float(4./10), vtexCoord.x);
		text = texture(colorMap, vec2(s, vtexCoord.y));    
	}
	else if (vtexCoord.x <= float(6./6) && vtexCoord.x >= float(5./6)) {
		float s = map (float(5./6), float(6./6), float(4./10), float(5./10), vtexCoord.x);
		text = texture(colorMap, vec2(s, vtexCoord.y));    
	}
	if (text.a < 0.5) discard;   
	else fragColor = text * vec4(0, 0, 1, 0);
}*/
