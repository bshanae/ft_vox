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

	enum			state
	{
		waiting,
		running,
		finished
	};

					timer();
	explicit		timer(float value);
	virtual			~timer() = default;

	enum state		get_state() const
	{
		return state;
	}

	float			get_progress() const;

	void 			execute();
	void 			reset();

	void			update();

private :

	state			state;
	optional<float>	total;

	float			last = 0.f;
	float			left = 0.f;
};