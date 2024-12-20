#version 330 core

layout(location = 0) in vec4 aPosition;
layout(location = 1) in vec3 aColor;

out vec3 vColor;

void main()
{
   gl_Position = aPosition;
   vColor = aColor;
}