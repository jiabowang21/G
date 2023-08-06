#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;

//I
uniform vec4 lightAmbient;
uniform vec4 lightDiffuse;
uniform vec4 lightSpecular;
uniform vec4 lightPosition;//(sempre estarà en eyespace)

//K
uniform vec4 matAmbient;
uniform vec4 matDiffuse;
uniform vec4 matSpecular;
uniform float matShininess;

void main()
{
    vec3 N = normalize(normalMatrix * normal);
	vec3 P = normalize((modelViewMatrix * vec4(vertex, 1.0)).xyz);	//object -> eye space
	vec3 V = -P;    
	vec3 L = normalize((lightPosition).xyz - P);
    vec3 R = 2 * (dot(N, L))* N - L;
    frontColor = matAmbient * lightAmbient + matDiffuse * lightDiffuse * max(0.0, dot(N, L)) + matSpecular * lightSpecular * pow(max(0.0, dot(R, V)), matShininess);
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}

/*
	Càlcul de la il·luminació per vèrtex amb el model de Phong
		(ka*Ia + kd*Id(N*L) + Ks*Is(R*V)^s 
		ka, kd, ks = reflectivitat ambient, difosa i especular del material (MATERIAL)
		s = shininess del material
		Ia, Id, Is = propietats ambient, difosa i especular de la llum (LLUM)
		N = vector normal unitari
		P = posició del vector en world space
		L = vector unitari cap a la font de llum
		V = vector unitari del vèrtex cap a la càmera
		R = reflexió del vector L respecte N. Es pot calcular com R = 2(N*L)N - L
		
	Cal evitar restar il·luminació quan els productes escalars N*L o R*V són negatius.
		max(0.0, dot(N, L)) // max(0.0, dot(R, V))


*/
