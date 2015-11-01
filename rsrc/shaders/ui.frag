#version 130

uniform sampler2D objectTexture;
uniform vec4 color;

in vec2 uv2;

out vec4 outColor;

void main()
{
	outColor = texture(objectTexture, vec2(uv2.x, uv2.y)) * 1 - (1 - color) / 4;
	/*
	outColor.r = outColor.r * outColor.a + 1.0 * (1 - outColor.a);
	outColor.a = 1.0;
	*/
}


