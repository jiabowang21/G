#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;
uniform float angle = 0.5;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    
	//mat4 trans = mat4(vec4(1,0,0,0), vec4(0,1,0,0), vec4(0,0,1,0), vec4(0,-1,0,1));
	//vec3 v = m * vertex;
	float d = length(vec2(1.45, 1.55));
	float inter = smoothstep(0, vertex.y, d);
	mat3 m = mat3(vec3(cos(angle), 0, -sin(angle)), vec3(0, 1, 0), vec3(sin(angle), 0, cos(angle))); //rotacio y
	vec3 v;
	vec3 n;
	if (vertex.y >= 1.45) {
		v = m * vertex;
		n = m * normal;
	 }
	else  {
		v = vertex;
		n = normal;
	}
	v = vec3(mix(vertex, v, inter));
	n = vec3(mix(normal, n, inter));
    vtexCoord = texCoord;
	frontColor = vec4(n.z);
    gl_Position = modelViewProjectionMatrix * vec4(v, 1.0);
}
/*
//Hecho con smoothstep
void main() {
	float radi = 0.2;
	float d = length(vec2(vtexCoord.x - 0.5, vtexCoord.y - 0.5));
	fragColor = vec4(1.0, vec2(smoothstep(radi, radi, d)), 1.0);
} */
