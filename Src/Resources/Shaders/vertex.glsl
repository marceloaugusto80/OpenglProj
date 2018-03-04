#version 330 core

uniform mat4 projection;

in vec4 position;
in vec2 uv;
in float texIndex;
in vec4 color;

out vec2 fUv;
out float fTexIndex;
out vec4 fColor;


void main()
{
	gl_Position = projection * position;
	fUv = uv;
	fTexIndex = texIndex;
	fColor = color;
}