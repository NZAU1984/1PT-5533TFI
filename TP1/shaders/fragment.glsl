#version 140

in vec3 normal;
in vec4 position_vs;

uniform vec4 color;

void main(void)
{
	gl_FragColor = color * (0.5f + 0.5f * normalize(normal).z);
}
