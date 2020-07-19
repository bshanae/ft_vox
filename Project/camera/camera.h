#pragma once

#include "common/OpenGL.h"
#include "common/aliases.h"
#include "common/global.h"

#warning "Move to .cpp"
#include "application/window.h"
#include "application/input.h"


class						camera : public global<camera>
{
	friend class				application;
public :
							camera()
	{
		recalculate();
	}
							~camera() override = default;

	static inline float		near_plane = 0.f;
	static inline float		far_plane = 1000.f;
	static inline float 	fov = 30.f;

	[[nodiscard]]
	static mat4		get_projection_matrix()
	{
		return(instance()->projection_matrix);
	}

	[[nodiscard]]
	static mat4		get_view_matrix()
	{
		return (instance()->view_matrix);
	}

	vec3					position = vec3(0.f, 0.0f, 1.6f);

	float					yaw = -90.f;
	float					pitch = 0.f;

private :

	const vec3				up_const = vec3(0.f, 1.f, 0.f);

	vec3					front = vec3(0.f, 0.f, -1.f);
	vec3					up = up_const;
	vec3					right = vec3(0.f, 0.f, 0.f);

	mat4					projection_matrix = mat4(0.f);
	mat4					view_matrix = mat4(0.f);

	void					update()
	{
		//position += vec3(0,0,0.01) ;

		if (input::get_keys().at(GLFW_KEY_W) == input::key_state::RELEASED)
		{
			position += vec3(0,0,-0.1) ;
			cerr << "hi1" << endl;
		}
		if (input::get_keys().at(GLFW_KEY_S) == input::key_state::RELEASED)
		{
			position += vec3(0,0,0.1);
			cerr << "hi2" << endl;
		}
		recalculate();
	}

	void					recalculate()
	{
		vec3				local_front;

#if 1 || VOX_DEBUG
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

//		projection_matrix = perspective(
//			radians(fov),
//			(float)window::size.x / (float)window::size.y,
//			near_plane,
//			far_plane);

		projection_matrix = glm::perspective(glm::radians(120.0f),
											 (float)window::size.x / (float)window::size.y,
											 0.001f,
											 1000.0f);
		view_matrix = lookAt(position, position + front, up);
	}
};