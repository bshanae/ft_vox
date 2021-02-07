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
	explicit		timer(float value);
					~timer() = default;

	bool 			is_running() const;
	bool 			did_finish() const;

private :

	void			update() const;

	mutable float	last = 0.f;
	mutable float	left = 0.f;
};