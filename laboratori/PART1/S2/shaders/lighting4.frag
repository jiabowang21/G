#version 330 core

uniform mat4 modelViewMatrix;

in vec4 frontColor;
out vec4 fragColor;
in vec3 normalN;
in vec3 vertexV;

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
    vec3 N = normalize(normalN);
	vec3 P = normalize((modelViewMatrix * vec4(vertexV, 1.0)).xyz);	//object -> eye space
	vec3 V = -P;    
	vec3 L = normalize((lightPosition).xyz - P);
    vec3 R = 2 * (dot(N, L))* N - L;
    fragColor = matAmbient * lightAmbient + matDiffuse * lightDiffuse * max(0.0, dot(N, L)) + matSpecular * lightSpecular * pow(max(0.0, dot(R, V)), matShininess);
}
