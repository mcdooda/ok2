#version 130

uniform sampler2D objectTexture;
uniform vec4 color;

in vec2 uv2;

out vec4 outColor;

void main()
{
	outColor = texture(objectTexture, vec2(uv2.x, 1 - uv2.y)) * color;
	/*
	outColor.r = outColor.r * outColor.a + 1.0 * (1 - outColor.a);
	outColor.a = 1.0;
	*/
}


