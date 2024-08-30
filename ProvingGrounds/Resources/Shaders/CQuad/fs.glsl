#version 330 core

in vec3 p_Color;

out vec4 o_FragmentColor;

void main()
{
    o_FragmentColor = vec4(p_Color, 1.0f);
}
