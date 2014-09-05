#version 130

in vec4 position;
in vec2 uv;

out vec2 uv2;

void main()
{
	gl_Position = position;
	uv2 = uv;
}


