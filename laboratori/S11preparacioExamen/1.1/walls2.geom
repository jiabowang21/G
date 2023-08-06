#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices=36) out;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 modelViewProjectionMatrixInverse;
uniform vec3 boundingBoxMax;
uniform vec3 boundingBoxMin;

in vec4 vfrontColor[];
out vec4 gfrontColor;

const vec4 GREEN = vec4(0, 1, 0, 1);
const vec4 RED = vec4(1, 0, 0, 1);
const vec4 BLUE = vec4(0, 0, 1, 1);

void floorVertex(bool x, bool z, vec3 RC, vec4 color) {
  	gfrontColor = color;
  	if (x) RC.x += (boundingBoxMax.x - boundingBoxMin.x)/2;
  	else RC.x -= (boundingBoxMax.x - boundingBoxMin.x)/2;
  	if (z) RC.z += (boundingBoxMax.z - boundingBoxMin.z)/2;
  	else RC.z -= (boundingBoxMax.z - boundingBoxMin.z)/2;
	RC.y = boundingBoxMin.y;
  	gl_Position = modelViewProjectionMatrix * vec4(RC, 1);
  	EmitVertex();
}

void floorVertex2(bool x, bool y, vec3 RC, vec4 color) {
  	gfrontColor = color;
  	if (x) RC.x += (boundingBoxMax.x - boundingBoxMin.x)/2;
  	else RC.x -= (boundingBoxMax.x - boundingBoxMin.x)/2;
  	if (y) RC.y += (boundingBoxMax.y - boundingBoxMin.y)/2;
  	else RC.y -= (boundingBoxMax.y - boundingBoxMin.y)/2;
	RC.z = boundingBoxMin.z;
  	gl_Position = modelViewProjectionMatrix * vec4(RC, 1);
  	EmitVertex();
}

void floorVertex3(bool x, bool y, vec3 RC, vec4 color) {
  	gfrontColor = color;
  	if (x) RC.z += (boundingBoxMax.z - boundingBoxMin.z)/2;
  	else RC.z -= (boundingBoxMax.z - boundingBoxMin.z)/2;
  	if (y) RC.y += (boundingBoxMax.y - boundingBoxMin.y)/2;
  	else RC.y -= (boundingBoxMax.y - boundingBoxMin.y)/2;
	RC.x = boundingBoxMax.x;
  	gl_Position = modelViewProjectionMatrix * vec4(RC, 1);
  	EmitVertex();
}

void floorVertex4(bool x, bool y, vec3 RC, vec4 color) {
  	gfrontColor = color;
  	if (x) RC.z += (boundingBoxMax.z - boundingBoxMin.z)/2;
  	else RC.z -= (boundingBoxMax.z - boundingBoxMin.z)/2;
  	if (y) RC.y += (boundingBoxMax.y - boundingBoxMin.y)/2;
  	else RC.y -= (boundingBoxMax.y - boundingBoxMin.y)/2;
	RC.x = boundingBoxMin.x;
  	gl_Position = modelViewProjectionMatrix * vec4(RC, 1);
  	EmitVertex();
}

void main(void) {
  	for (int i = 0; i < 3; ++i) {
    	gfrontColor = vfrontColor[i];
    	gl_Position = gl_in[i].gl_Position;
		/*
		if (0 >= (modelViewMatrix * vec4(boundingBoxMin, 1.0)).x && 0 <= (modelViewMatrix * vec4(boundingBoxMax, 1.0)).x && 0 >= (modelViewMatrix * vec4(boundingBoxMin, 1.0)).y && 0 <= (modelViewMatrix * vec4(boundingBoxMax, 1.0)).y && 0 >= (modelViewMatrix * vec4(boundingBoxMin, 1.0)).z && 0 <= (modelViewMatrix * vec4(boundingBoxMax, 1.0)).z) {
			gfrontColor = vfrontColor[i] * 2;		
		}*/
		vec4 PosMin = modelViewMatrix * vec4(boundingBoxMin, 1.0);
		vec4 init = vec4(0.0);
		vec4 PosMax = modelViewMatrix * vec4(boundingBoxMax, 1.0);
		if (all(greaterThanEqual(vec3(init.xyz), vec3(PosMin.xyz))) && all(lessThanEqual(vec3(init.xyz), vec3(PosMax.xyz)))) {
			gfrontColor = vfrontColor[i] * 2;
		}
    	EmitVertex();
  	}
  	EndPrimitive();
  	if (gl_PrimitiveIDIn == 0) { 
    	vec3 RC = (boundingBoxMax + boundingBoxMin);
    	floorVertex(false, false, RC, GREEN);//(esquerra adalt)
    	floorVertex(true, false, RC, GREEN);//(dreta adalt)
    	floorVertex(false, true, RC, GREEN);//(esquerra abaix)
    	floorVertex(true, true, RC, GREEN);//(dreta abaix)
    	EndPrimitive();
    	floorVertex2(false, false, RC, BLUE);//(esquerra adalt)
    	floorVertex2(true, false, RC, BLUE);//(dreta adalt)
    	floorVertex2(false, true, RC, BLUE);//(esquerra abaix)
    	floorVertex2(true, true, RC, BLUE);//(dreta abaix)
    	EndPrimitive();
    	floorVertex3(false, false, RC, RED);//(esquerra adalt)
    	floorVertex3(true, false, RC, RED);//(dreta adalt)
    	floorVertex3(false, true, RC, RED);//(esquerra abaix)
    	floorVertex3(true, true, RC, RED);//(dreta abaix)
    	EndPrimitive();
    	floorVertex4(false, false, RC, RED);//(esquerra adalt)
    	floorVertex4(true, false, RC, RED);//(dreta adalt)
    	floorVertex4(false, true, RC, RED);//(esquerra abaix)
    	floorVertex4(true, true, RC, RED);//(dreta abaix)
    	EndPrimitive();
  	}
}
