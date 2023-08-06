#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
in vec3 V;
out vec4 fragColor;

void main()
{
    vec3 N = normalize(cross(dFdx(V), dFdy(V)));
    fragColor = frontColor*N.z;
}
