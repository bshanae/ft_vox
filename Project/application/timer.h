#pragma once

#include "common/OpenGL.h"
#include "common/aliases.h"
#include "common/property.h"

class				timer
{
	friend class	application;

public :

	enum class 		state
	{
		waiting,
		running,
		finished
	};

					property<read_only, state, timer>
	    			state;

					timer()
	{
		state = state::waiting;
	}

	explicit		timer(float value) : timer()
	{
		total = value;
	}

	virtual			~timer() = default;

	void			operator () ()
	{
		assert(total and "Can't execute timer");

		left = *total;
		last = glfwGetTime();
		state = state::running;
	}

	virtual void	update()
	{
		if (state == state::running)
		{
			auto	current = glfwGetTime();

			left -= current - last;
			last = current;

			if (left <= 0.f)
			{
				state = state::finished;
				left = 0.f;
			}
		}
	}

	float			progress() const
	{
		if (not total)
			return (0.f);
		if (left < 0.f)
			return (1.f);
		return ((*total - left) / *total);
	}

protected :

	optional<float>	total;

	float			last = 0.f;
	float			left = 0.f;
};