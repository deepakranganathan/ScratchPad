#version 330 core
  
layout (location = 0) in vec3 position; // The position variable has attribute location 0
layout (location = 1) in vec3 color;	// The color variable has attribute location 1

out vec4 vertexColor; // Specify color to pass to fragment shader

void main()
{
    gl_Position = vec4(position, 1.0);
	vertexColor = vec4(color, 1.0);
}