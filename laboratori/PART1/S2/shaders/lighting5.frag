#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec3 normalN;
in vec3 vertexV;
uniform bool world;

uniform mat3 normalMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrixInverse;
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


vec4 light(vec3 N, vec3 V, vec3 L) {  
	N = normalize(N); V = normalize(V); L = normalize(L);  
	vec3 R = normalize(2.0 * dot(N, L) * N - L);  
	float NdotL = max(0.0, dot(N, L));  
	float RdotV = max(0.0, dot(R,V));  
	float Idiff = NdotL;  
	float Ispec = 0;  
	if (NdotL > 0) Ispec = pow(RdotV, matShininess);  
	return    
		matAmbient  * lightAmbient +    
		matDiffuse  * lightDiffuse * Idiff+    
		matSpecular * lightSpecular * Ispec;
}

void main()
{
	vec3 N, P, V, L;
	if (world == true) {
		N = normalize(normalN);
		P = normalize((modelMatrix * vec4(vertexV, 1.0)).xyz);	//object -> eye spac
		V = -P;    
		L = normalize((viewMatrixInverse * (lightPosition)).xyz - P);   
		fragColor = light(N, V, L);	
	}
	else { 
		N = normalize(normalMatrix * normalN); 
		P = normalize((modelViewMatrix * vec4(vertexV, 1.0)).xyz);	//object -> eye space
		V = -P;    
		L = normalize((lightPosition).xyz - P);    
		fragColor = light(N, V, L);			
	}
} 
