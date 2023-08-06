#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;
uniform int mode = 2;
uniform vec4 matAmbient, matDiffuse, matSpecular; 
uniform float matShininess; 
uniform vec4 lightAmbient, lightDiffuse, lightSpecular, lightPosition;
uniform mat4 modelViewMatrix;

const vec4 N = vec4(0.0);

bool isInCircle(vec2 centre, float rad, vec2 point) {
	return distance(centre, point) <= rad;
}

void mode0() {
	vec2 C = vec2(0, 0);
	float r = 1;
	if (isInCircle(C, r, vtexCoord)) fragColor = N;
    else discard;
}

void mode1() {
	vec3 NN = vec3(vtexCoord.x, vtexCoord.y, sqrt(1- pow(vtexCoord.x, 2) - pow(vtexCoord.y, 2)));	
	vec3 PP = NN;	
	fragColor = vec4(NN.z);
}

void mode2() {
	vec3 NN = vec3(vtexCoord.x, vtexCoord.y, sqrt(1- pow(vtexCoord.x, 2) - pow(vtexCoord.y, 2)));	
	vec3 PP = NN;	
	vec3 normal = (modelViewMatrix * vec4(NN, 0.0)).xyz;
	vec3 point = normalize((modelViewMatrix * vec4(PP, 1.0)).xyz);
	vec3 V = -point;
	vec3 L = normalize((lightPosition).xyz - point);
	vec3 R = 2 * (dot(normal, L))* normal - L;
	fragColor = matAmbient * lightAmbient + matDiffuse * lightDiffuse * max(0.0, dot(normal, L)) + matSpecular * lightSpecular * pow(max(0.0, dot(R, V)), matShininess); 
}	

void main()
{
	if (mode == 0) {	
		mode0();
	}
	else if (mode == 1) {
		mode0();
		mode1();
	}
	else if (mode == 2) {
		mode0();		
		mode2();
	}
}
