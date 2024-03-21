#version 330 core
layout(location = 0) in vec3 vertexPos;
layout(location = 1) in vec3 ourColor;

out vec3 vertexColor;

void main()
{
	gl_Position = vec4(vertexPos, 1.0);
	vertexColor = ourColor;
}
