#pragma once

#include "common/opengl.h"
#include "common/aliases.h"
#include "common/property.h"

namespace								engine
{
	class								timer;
}

class									engine::timer
{
public :

	enum								state
	{
		waiting,
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
		state = waiting;
	}

	explicit							timer(float value) : timer()
	{
		total = value;
	}

	virtual								~timer() = default;

	void 								execute()
	{
		assert(total and "Can't start timer");

		left = *total;
		last = glfwGetTime();
		state = running;
	}

	void 								reset()
	{
		state = waiting;
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
		if (state.value == running)
		{
			auto						current = (float)glfwGetTime();

			left -= current - last;
			last = current;

			if (left <= 0.f)
			{
				state.value = finished;
				left = 0.f;
			}
		}
	}
};