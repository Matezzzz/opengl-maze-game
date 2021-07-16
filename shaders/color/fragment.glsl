#version 330 core

out vec4 result_color;

uniform vec3 color;

void main()
{
    result_color = vec4(color, 1.f);
}
