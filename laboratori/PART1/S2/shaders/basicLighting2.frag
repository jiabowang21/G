#version 330 core

in vec3 Norm;
in vec4 frontColor;
out vec4 fragColor;

void main()
{
    vec3 NN = normalize(Norm);
    fragColor = frontColor * NN.z;
}
