#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;
uniform int N = 300;
uniform int mode = 0;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

void cubeVertex(float x, float y, float z, vec3 C, vec4 color) {
  	gfrontColor = color;
  	vec3 V = vec3(x, y, z);
	mat4 T = mat4(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, 1, 0), vec4(C, 1)); 
  	gl_Position = modelViewProjectionMatrix * vec4(V + C, 1);
  	EmitVertex();
}

void paintCube(vec3 C, vec4 color) {
  	// front
  	cubeVertex(0, 0, 1, C, color);
  	cubeVertex(1, 0, 1, C, color);
  	cubeVertex(0, 1, 1, C, color);
  	cubeVertex(1, 1, 1, C, color);
  	EndPrimitive();
  	// back
  	cubeVertex(0, 1, 0, C, color);
  	cubeVertex(1, 1, 0, C, color);
  	cubeVertex(0, 0, 0, C, color);
  	cubeVertex(1, 0, 0, C, color);
  	EndPrimitive();
  	// left
  	cubeVertex(0, 0, 0, C, color);
  	cubeVertex(0, 0, 1, C, color);
  	cubeVertex(0, 1, 0, C, color);
  	cubeVertex(0, 1, 1, C, color);
  	EndPrimitive();
  	// right
  	cubeVertex(1, 1, 0, C, color);
  	cubeVertex(1, 1, 1, C, color);
  	cubeVertex(1, 0, 0, C, color);
  	cubeVertex(1, 0, 1, C, color);
  	EndPrimitive(); 
  	// top
  	cubeVertex(0, 1, 1, C, color);
  	cubeVertex(1, 1, 1, C, color);
  	cubeVertex(0, 1, 0, C, color);
  	cubeVertex(1, 1, 0, C, color);
  	EndPrimitive();
  	// bottom
  	cubeVertex(1, 0, 0, C, color);
  	cubeVertex(1, 0, 1, C, color);
  	cubeVertex(0, 0, 0, C, color);
  	cubeVertex(0, 0, 1, C, color);
  	EndPrimitive();
}
void main( void )
{
	if (gl_PrimitiveIDIn%N == 0) {
		vec3 C = (gl_in[0].gl_Position.xyz + gl_in[1].gl_Position.xyz + gl_in[2].gl_Position.xyz)/3;
		C /= 2;
  		C.x= floor(C.x + 0.5);
  		C.y= floor(C.y + 0.5);
  		C.z= floor(C.z + 0.5); 
  		C *= 2; 
		vec4 color = (vfrontColor[0] + vfrontColor[1] + vfrontColor[2])/3;
		paintCube(C, color);
	}
}
