#include "camera.h"

#include "common/debug.h"
#include "application/window.h"
#include "application/input.h"

					camera::camera()
{
	recalculate();
}

void				camera::update()
{
//					Axis X
	if (input::is_pressed_or_held(GLFW_KEY_A))
		position.x -= 0.1;
	else if (input::is_pressed_or_held(GLFW_KEY_D))
		position.x += 0.1;

//					Axis y
	if (input::is_pressed_or_held(GLFW_KEY_Q))
		position.y -= 0.1;
	else if (input::is_pressed_or_held(GLFW_KEY_E))
		position.y += 0.1;

//					Axis Z
	if (input::is_pressed_or_held(GLFW_KEY_W))
		position.z -= 0.1;
	else if (input::is_pressed_or_held(GLFW_KEY_S))
		position.z += 0.1;
	recalculate();
}

void					camera::recalculate()
{
	vec3				local_front;

#if VOX_DEBUG
	cerr <<
		 "Camera : position = " <<
		 glm::to_string(position) <<
		 ", yaw = " << yaw <<
		 ", pitch = " << pitch << endl;
#endif

	local_front.x = cos(radians(yaw)) * cos(radians(pitch));
	local_front.y = sin(radians(pitch));
	local_front.z = sin(radians(yaw)) * cos(radians(pitch));
	front = normalize(local_front);
	right = normalize(cross(front, up_const));
	up = normalize(cross(right, front));

	projection_matrix = perspective(
		radians(fov),
		(float)window::size.x / (float)window::size.y,
		near_plane,
		far_plane);
	view_matrix = lookAt(position, position + front, up);
}