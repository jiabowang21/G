#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewProjectionMatrixInverse;
uniform vec3 boundingBoxMax;
uniform vec3 boundingBoxMin;

const vec4 BLACK=vec4(0, 0, 0, 1);
const vec4 CYAN=vec4(0, 1, 1, 1);

void floorVertex(bool x, bool z, vec3 RC, float R) {
  	gfrontColor=CYAN;
  	if (x) RC.x += R;
  	else RC.x -= R;
  	if (z) RC.z += R;
  	else RC.z -= R;
  	gl_Position = modelViewProjectionMatrix * vec4(RC, 1);
  	EmitVertex();
}

void main( )
{
	//floor cian
	if (gl_PrimitiveIDIn == 0) {
		float R = length(boundingBoxMax - boundingBoxMin)/2; //meitat de la capsa engoblant
    	vec3 RC = (boundingBoxMax + boundingBoxMin)/2;	//centre de la capsa englobant
    	RC.y = boundingBoxMin.y - 0.01;
    	floorVertex(false, false, RC, R); //esquerra darrere
    	floorVertex(true, false, RC, R); //dreta darrere
    	floorVertex(false, true, RC, R); //esquerra davant
    	floorVertex(true, true, RC, R); //dreta davant
    	EndPrimitive();
	}

	for( int i = 0 ; i < 3 ; i++)
	{
		gfrontColor = vfrontColor[i];
		gl_Position = gl_in[i].gl_Position;		
		EmitVertex(); 
	}
	EndPrimitive();
	
	for (int i = 0; i < 3; i++ ) {
		gfrontColor = vec4(0);
		vec4 aux = gl_Position;
		aux = modelViewProjectionMatrixInverse * gl_in[i].gl_Position;
		aux.y = boundingBoxMin.y;
		gl_Position = modelViewProjectionMatrix * aux;
		EmitVertex();
	}
	EndPrimitive();

}
