#include "timer.h"

#include "application/common/debug/debug.h"

using namespace		engine;

					timer::timer()
{
	state = waiting;
}

					timer::timer(float value) : timer()
{
	total = value;
}

float				timer::get_progress() const
{
	if (not total)
		return (0.f);
	if (left < 0.f)
		return (1.f);

	return (*total - left) / *total;
}

void 				timer::execute()
{
	if (!debug::check(total != nullopt, "[timer] Can't start timer"))
		return;

	left = *total;
	last = (float)glfwGetTime();
	state = running;
}

void 				timer::reset()
{
	state = waiting;
}

void				timer::update()
{
	if (state == running)
	{
		auto	current = (float)glfwGetTime();

		left -= current - last;
		last = current;

		if (left <= 0.f)
		{
			state = finished;
			left = 0.f;
		}
	}
}