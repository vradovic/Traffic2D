#version 330 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec2 a_TexCoord;

out vec2 v_TexCoord;

uniform vec4 u_TexCoordOffset;

void main()
{	
	v_TexCoord = a_TexCoord * u_TexCoordOffset.zw + u_TexCoordOffset.xy;

	gl_Position = a_Position;
}