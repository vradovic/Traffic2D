#version 330 core

layout(location = 0) in vec4 aPosition;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;

void main()
{
   gl_Position = aPosition;
   v_TexCoord = texCoord;
}