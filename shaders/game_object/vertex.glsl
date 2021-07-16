#version 330 core

layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec3 a_normal;

uniform mat4 model_matrix;
uniform mat4 view_projection_matrix;

out vec3 fragment_position;
out vec3 fragment_normal;
out vec4 fragment_pos_light_space;
out float dist;

uniform vec3 player_position;
uniform vec3 middle;
uniform mat4 light_matrix;

void main()
{
    dist = max(0, length(player_position - middle) - 25);
    vec4 position = model_matrix * vec4(a_pos.xy, a_pos.z - pow(1.3, dist), 1.0);
    gl_Position = view_projection_matrix * position;
    fragment_position = position.xyz;
    fragment_normal = a_normal;
    fragment_pos_light_space = light_matrix * position;
}
