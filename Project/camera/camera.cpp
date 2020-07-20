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
		position -= 0.1f * right;
	else if (input::is_pressed_or_held(GLFW_KEY_D))
		position += 0.1f * right;

//					Axis y
	if (input::is_pressed_or_held(GLFW_KEY_Q))
		position -= 0.1f * up;
	else if (input::is_pressed_or_held(GLFW_KEY_E))
		position += 0.1f * up;

//					Axis Z
	if (input::is_pressed_or_held(GLFW_KEY_W))
		position += 0.1f * front;
	else if (input::is_pressed_or_held(GLFW_KEY_S))
		position -= 0.1f * front;
	recalculate();
}

void					camera::recalculate()
{
	vec3				local_front;
	yaw += input::get_mouse_offset().x * sensitivity;
	pitch +=  input::get_mouse_offset().y * sensitivity;

#warning "Fix this"
	input::instance()->set_mouse_offset(ivec2(0));

	if(pitch > 89.0f)
		pitch =  89.0f;
	if(pitch < -89.0f)
		pitch = -89.0f;

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