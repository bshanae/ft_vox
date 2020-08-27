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
uniform int			uniform_apply_water_tint;

void				main()
{
	vec4			color;

	color = texture(uniform_texture, pass_texture_coordinates);
	color.xyz *= pass_light_level;

	if (color.a < uniform_alpha_discard_floor)
		discard;

	float			visibility;

	visibility = exp(-pow(pass_distance_to_camera * uniform_fog_density, uniform_fog_gradient));
	visibility = clamp(visibility, 0.f, 1.f);
	color.xyz = mix(uniform_background, color.xyz, visibility);

	if (uniform_apply_water_tint == 1)
		color = mix(color, vec4(0, 0.16, 1.0, 1.0), 0.45);

	out_color = color;
}