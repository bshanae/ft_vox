#version 400 core

in vec3         in_position;

uniform mat4    uniform_projection;
uniform mat4    uniform_view;

out vec3        pass_position;

void            main()
{
    pass_position = in_position;
    gl_Position = vec4(in_position, 1.0);
}