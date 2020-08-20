#version 400 core

in vec2     		pass_texture_coordinates;
in float			pass_light_level;
in float			pass_distance_to_camera;

out vec4			out_color;

uniform sampler2D	uniform_texture;
uniform float		uniform_alpha_discard_floor;
uniform vec3		uniform_background;
uniform float		uniform_fog_density;
uniform float		uniform_fog_gradient;

void				main()
{
	vec4			temp_color;

	temp_color = texture(uniform_texture, pass_texture_coordinates);
	temp_color.xyz *= pass_light_level;

	if (temp_color.a < uniform_alpha_discard_floor)
		discard;

	float			visibility;

	visibility = exp(-pow(pass_distance_to_camera * uniform_fog_density, uniform_fog_gradient));
	visibility = clamp(visibility, 0.f, 1.f);
	temp_color.xyz = mix(uniform_background, temp_color.xyz, visibility);

	out_color = temp_color;

//	out_color = vec4(uniform_alpha_discard_floor, 0, 0, 1);
}