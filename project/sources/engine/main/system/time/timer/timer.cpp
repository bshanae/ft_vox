#include "timer.h"

#include "application/common/debug/debug.h"

using namespace		engine;

					timer::timer()
{
	last = (float)glfwGetTime();
	left = -1.f;
}

					timer::timer(float value)
{
	last = (float)glfwGetTime();
	left = value;
}

bool 				timer::is_running() const
{
	update();
	return left > 0.f;
}

bool 				timer::did_finish() const
{
	update();
	return left < 0.f;
}

void				timer::update() const
{
	const auto		current = (float)glfwGetTime();

	left -= current - last;
	last = current;
}