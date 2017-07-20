#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 color;

void main()
{
	color = vec4(1.0, 0.8, 0.25, 1.0);
}