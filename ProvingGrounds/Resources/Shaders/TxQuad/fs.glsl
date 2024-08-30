#version 330 core

in vec2 p_TexPos;

out vec4 o_FragmentColor;

uniform sampler2D texture0;

void main()
{
    o_FragmentColor = texture(texture0, p_TexPos);
}
