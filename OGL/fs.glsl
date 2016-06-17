#version 330 core

in vec4 vertexColor;
in vec2 TexCoord;
out vec4 color;

uniform vec4 myColor;
uniform sampler2D myTexture1;
uniform sampler2D myTexture2;

void main()
{
    //color = ourColor;
	color = mix(texture(myTexture1, TexCoord), texture(myTexture2, vec2(1.0f-TexCoord.x,TexCoord.y)), 0.2);
} 