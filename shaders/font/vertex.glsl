#version 330 core

layout(location = 0) in vec4 a_vertex_data;
out vec2 tex_coords;

uniform mat4 MVP;

void main()
{
    gl_Position = MVP * vec4(a_vertex_data.xy, 0.0, 1.0);
    tex_coords = a_vertex_data.zw;
}
