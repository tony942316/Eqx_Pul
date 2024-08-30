#version 330 core

layout (location = 0) in vec3 i_Pos;
layout (location = 1) in vec2 i_TexPos;

out vec2 p_TexPos;

uniform mat4 u_Projection;

void main()
{
    p_TexPos = i_TexPos;
    gl_Position = u_Projection * vec4(i_Pos, 1.0f);
}
