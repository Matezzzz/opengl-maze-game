#version 330 core

in vec2 tex_coords;

out vec4 o_color;

uniform sampler2D text;
uniform vec3 text_color;

void main()
{
    o_color = vec4(text_color, texture(text, tex_coords).r);
}
