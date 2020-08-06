#version 400 core

layout (location = 0) in vec3	in_position;
layout (location = 1) in vec2	in_texture_coordinates;
layout (location = 2) in float	in_light_level;

out vec2						pass_texture_coordinates;
out float						pass_light_level;

uniform mat4					uniform_projection;
uniform mat4					uniform_view;
uniform mat4					uniform_transformation;

void							main()
{
	pass_texture_coordinates = in_texture_coordinates;
	pass_light_level = in_light_level;

	gl_Position = uniform_projection * uniform_view * uniform_transformation * vec4(in_position, 1.0);
}