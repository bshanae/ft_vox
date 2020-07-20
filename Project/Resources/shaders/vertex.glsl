#version 400 core

in vec3         in_position;

uniform mat4    uniform_projection;
uniform mat4    uniform_view;

out vec4        pass_position;

void            main()
{
    pass_position = uniform_projection * uniform_view * vec4(in_position, 1.0);
    gl_Position = pass_position;
}