#pragma once

#include "application/common/imports/opengl.h"
#include "application/common/imports/std.h"

namespace			engine
{
	class			timer;
}

class				engine::timer
{
public :

					timer();
	explicit		timer(float duration);
					~timer() = default;

	bool 			is_running() const;
	bool 			did_finish() const;

private :

	float			finish_time;

	static float 	get_finish_time(float duration);
};