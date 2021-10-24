#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aTextureCoords;

uniform vec4 OurColor;

out vec4 VertexColor;
out vec2 TextureCoords;

void main()
{
	gl_Position = vec4(aPosition, 1.0);
	VertexColor = aColor;
	TextureCoords = aTextureCoords;
}