#version 330 core
layout(location = 0) in vec3 FragColor;

void main()
{
	gl_Position = vec4(FragColor, 1.0);
}