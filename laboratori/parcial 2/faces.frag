#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;
uniform sampler2D photo;  // exemple: football.jpg    
uniform sampler2D mask1;  // exemple: mask1.jpg; observeu el dígit "1" al final del nom del sampler 
uniform int mode = 4;

void main()
{
	float p = texture(mask1, vtexCoord).p;

	if (mode == 0) {
		fragColor = texture(photo, vtexCoord);
	}

	else if (mode == 1) {
		if (p < 0.1) fragColor = texture(photo, vtexCoord);
		else fragColor = vec4(0);
	}

	else if (mode == 2) {
		fragColor = mix(texture(photo, vtexCoord), vec4(1), 0.9*p);
	}
	
	else if (mode == 3) {
		fragColor = texture(photo, vec2(vtexCoord.s, vtexCoord.t + p/200*sin(200*vtexCoord.s)));
	}
	
	else if (mode == 4) {
		vec4 M1;
		vec4 M2;
		vec4 M3;
		vec4 M4;
		vec4 M5;
		vec4 M6;	
		vec4 M7;
		vec4 M8;
		vec4 M9;
		//1		
		M1 = texture(photo, vec2(vtexCoord.s + float(1/256), vtexCoord.t));
		//2
		M2 = texture(photo, vec2(vtexCoord.s + float(1/256), vtexCoord.t - float(1/256)));
		//3
		M3 = texture(photo, vec2(vtexCoord.s + float(1/256), vtexCoord.t + float(1/256)));
		//4
		M4 = texture(photo, vec2(vtexCoord.s, vtexCoord.t + float(1/256)));
		//5
		M5 = texture(photo, vec2(vtexCoord.s, vtexCoord.t));
		//6
		M6 = texture(photo, vec2(vtexCoord.s, vtexCoord.t - float(1/256)));
		//7
		M7 = texture(photo, vec2(vtexCoord.s - float(1/256), vtexCoord.t));
		//8		
		M8 = texture(photo, vec2(vtexCoord.s - float(1/256), vtexCoord.t - float(1/256)));
		//9
		M9 = texture(photo, vec2(vtexCoord.s - float(1/256), vtexCoord.t + float(1/256)));
		vec3 M = vec3 ((M1.xyz + M2.xyz + M3.xyz + M4.xyz + M5.xyz + M6.xyz + M7.xyz + M8.xyz + M9.xyz) / 9);

		fragColor = mix(texture(photo, vtexCoord), vec4(M, 0), p);
	}	

}
