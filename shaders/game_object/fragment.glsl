#version 330 core

out vec4 o_color;

in vec3 fragment_position;
in vec3 fragment_normal;
in vec4 fragment_pos_light_space;
in float dist;

struct objectMaterial
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct directionalLight
{
    vec3 direction;
    vec3 color;
};

uniform directionalLight light;
uniform objectMaterial material;
uniform vec3 camera_position;
uniform sampler2D shadow_map;

void main()
{
    vec3 ambient = material.ambient * light.color;

    vec3 light_dir = normalize(-light.direction);
    vec3 norm = normalize(fragment_normal);
    vec3 diffuse = light.color * (material.diffuse * max(dot(norm, light_dir), 0.0));

    vec3 view_direction = normalize(camera_position - fragment_position);
    vec3 reflect_direction = reflect(-light_dir, norm);
    vec3 specular = light.color * (material.specular * pow(max(0.0, dot(view_direction, reflect_direction)), material.shininess));

    vec3 projected_coords = fragment_pos_light_space.xyz / fragment_pos_light_space.w * 0.5 + vec3(0.5);

    float closest_depth = texture(shadow_map, projected_coords.xy).r;
    float current_depth = projected_coords.z;

    float bias = 0.005f;
    float shadow = 0.0;
    vec2 texel_size = 1.0 / textureSize(shadow_map, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcf_depth = texture(shadow_map, projected_coords.xy + vec2(x, y) * texel_size).r;
            shadow += current_depth - bias > pcf_depth ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;
    if (projected_coords.x < 0 || projected_coords.x > 1 || projected_coords.y < 0 || projected_coords.y > 1 || projected_coords.z < 0 || projected_coords.z > 1)
    {
        shadow = 0.0;
    }

    o_color = vec4((ambient + (1.1 - shadow) * (diffuse + specular)), 1.0);
    //o_color = vec4(1000 * vec3(current_depth - closest_depth), 1.0);
}


