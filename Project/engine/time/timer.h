#pragma once

#include "common/OpenGL.h"
#include "common/aliases.h"
#include "common/property.h"

class									timer
{
public :

	enum class 							state
	{
		deferred,
		running,
		finished
	};

	property<read_only, state, timer>	state;

										timer()
	{
		state.getter = [this](){
			update();
			return (state.value);
		};
		state.prohibit_direct_access();
		state = state::deferred;
	}

	explicit							timer(float value) : timer()
	{
		total = value;
	}

	virtual								~timer() = default;

	void								operator () ()
	{
		assert(total and "Can't execute timer");

		left = *total;
		last = glfwGetTime();
		state = state::running;
	}

	float								progress() const
	{
		if (not total)
			return (0.f);
		if (left < 0.f)
			return (1.f);
		return ((*total - left) / *total);
	}

private :

	optional<float>						total;

	float								last = 0.f;
	float								left = 0.f;

	void								update()
	{
		if (state.value == state::running)
		{
			auto						current = (float)glfwGetTime();

			left -= current - last;
			last = current;

			if (left <= 0.f)
			{
				state.value = state::finished;
				left = 0.f;
			}
		}
	}
};