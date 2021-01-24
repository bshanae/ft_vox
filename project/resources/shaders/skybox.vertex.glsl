#version 330 core

layout (location = 0) in vec3	position;

out vec3						texture_coordinates;

uniform mat4					uniform_projection;
uniform mat4					uniform_view;

void							main()
{
	texture_coordinates = position;
	gl_Position = (uniform_projection * uniform_view * vec4(position, 1.0)).xyww;
}