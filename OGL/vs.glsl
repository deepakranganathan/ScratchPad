#version 330 core
  
layout (location = 0) in vec3 position; // The position variable has attribute location 0
layout (location = 1) in vec3 color;	// The color variable has attribute location 1
layout (location = 2) in vec2 texCoord;	// The texCoord variable has attribute location 2

out vec4 vertexColor; // Specify color to pass to fragment shader
out vec2 TexCoord;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(position, 1.0f);
	vertexColor = vec4(color, 1.0f);
	TexCoord	= vec2(texCoord.x, 1.0f - texCoord.y);  // Invert y-axis
}