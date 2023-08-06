#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
in vec3 normalO[];
out vec4 gfrontColor;

uniform float time;
uniform mat4 modelViewProjectionMatrix;

const float speed = 0.5;

const float angSpeed = 8.0; 

void main( void )
{
	vec3 n = speed * time * (normalO[0] + normalO[1] + normalO[2])/3;

	//baricentre triangle
	vec3 BT = (gl_in[0].gl_Position.xyz + gl_in[1].gl_Position.xyz + gl_in[2].gl_Position.xyz)/3; 

	//angle rotació
	float a = angSpeed * time;

	//matriu rotacio
	mat3 Rz = mat3 (vec3(cos(a), sin(a), 0), 
					vec3(-sin(a), cos(a), 0),
					vec3(0, 0, 1));
	
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];

		vec3 V = gl_in[i].gl_Position.xyz - BT;	//portar-ho al baricentre

		V = Rz * V;								//rotar sobre eix Z
	
		V += BT + n;							//traslladar al destí 
	
		gl_Position = modelViewProjectionMatrix * vec4(V, 1.0);
		
		EmitVertex();
	} 
    EndPrimitive();
}
