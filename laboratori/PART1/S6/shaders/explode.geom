#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
in vec3 normalO[];
out vec4 gfrontColor;

uniform float time;
uniform mat4 modelViewProjectionMatrix;

const float speed = 1.2;

void main( void )
{
	vec3 n = speed * time * (normalO[0] + normalO[1] + normalO[2])/ 3;

	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
	
		vec3 trans = gl_in[i].gl_Position.xyz + n;
		gl_Position = modelViewProjectionMatrix * vec4(trans, 1.0);
		
		EmitVertex();
	} 
    EndPrimitive();
}
