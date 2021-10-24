#version 330 core

out vec4 FragColor;

in vec4 VertexColor;
in vec2 TextureCoords;

uniform sampler2D Texture0;
uniform sampler2D Texture1;

void main()
{
   //FragColor = VertexColor;
   FragColor = mix(texture(Texture0, TextureCoords), texture(Texture1, TextureCoords), 0.2) * VertexColor;
}