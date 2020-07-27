#version 400 core

in vec3			in_position;
in vec2			in_texture_coordinates;

out vec2		pass_texture_coordinates;

uniform mat4	uniform_projection;
uniform mat4	uniform_view;
uniform mat4	uniform_transformation;

void			main()
{
	pass_texture_coordinates = in_texture_coordinates;
	gl_Position = uniform_projection * uniform_view * uniform_transformation * vec4(in_position, 1.0);
}