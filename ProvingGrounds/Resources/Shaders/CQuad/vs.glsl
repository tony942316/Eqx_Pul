#version 330 core

layout (location = 0) in vec3 i_Pos;
layout (location = 1) in vec3 i_Color;

out vec3 p_Color;

uniform mat4 u_Projection;

void main()
{
    p_Color = i_Color;
    gl_Position = u_Projection * vec4(i_Pos, 1.0f);
}
