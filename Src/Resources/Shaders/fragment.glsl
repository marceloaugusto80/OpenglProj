#version 330 core

uniform sampler2DArray texArray;

in vec2 fUv;
in float fTexIndex;
in vec4 fColor;

out vec4 color;



void main()
{
	if (fTexIndex < 0)
	{
		color = fColor;
	}
	else
	{
		color = texture(texArray, vec3(fUv.xy, fTexIndex)) * fColor;

	}
}