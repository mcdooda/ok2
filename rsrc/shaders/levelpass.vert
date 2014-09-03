#version 130

uniform mat4 modelMatrix;
uniform mat4 vpMatrix;

in vec2 position;
in vec2 uv;

out vec2 uv2;

void main()
{
	gl_Position = vpMatrix * modelMatrix * vec4(position, 0.0, 1.0);
	uv2 = uv;
}


