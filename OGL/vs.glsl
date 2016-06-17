#version 330 core
  
layout (location = 0) in vec3 position;

out vec4 vertexColor; // Specify color to pass to fragment shader

void main()
{
    gl_Position = vec4(position, 1.0);
	vertexColor = vec4(1.0f, 0.0f, 0.5f, 1.0f);
}