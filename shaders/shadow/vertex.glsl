#version 330 core
layout (location = 0) in vec3 aPos;

uniform vec3 player_position;
uniform vec3 middle;
uniform mat4 light_matrix;
uniform mat4 model_matrix;

void main()
{
    float dist = max(0, length(player_position - middle) - 25);
    gl_Position = light_matrix * model_matrix * vec4(aPos.xy, aPos.z - pow(1.3, dist), 1.0);
}
