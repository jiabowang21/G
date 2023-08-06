#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;
uniform sampler2D explosion;

float s1 = float(0.);
float s2 = float(1./8);
float t1 = float(5./6);
float t2 = float(1.);

uniform float time;

float map (float a, float b, float c, float d, float x) {
    return (x - a) / (b - a) * (d - c) + c;
}

void main()
{
    float slice = 1.0/30;					//es mostra cada 1/30 segons
    int frame = int(mod(time/slice, 48));	//per trobar a quin frame li toca 0, 1, 2,..., 47
    int x = frame%8;						//coordenada x
    int y = 5 - frame/8;					//coordenada y

    vec2 texCoord = vtexCoord;
    texCoord.x = texCoord.x + x/8.0;					
    texCoord.y = texCoord.y + y/6.0;
    fragColor = texture(explosion, texCoord);
    fragColor = fragColor * fragColor.w; 	//componente w = alpha
} 
