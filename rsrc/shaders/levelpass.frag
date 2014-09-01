#version 130

uniform sampler2D objectTexture;

in vec2 uv2;

out vec4 outColor;

void main()
{
	outColor = texture(objectTexture, vec2(uv2.x, 1 - uv2.y));
}


