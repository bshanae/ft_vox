#include "timer.h"

#include "application/common/debug/debug.h"

using namespace		engine;

					timer::timer() : finish_time(0)
{
}

					timer::timer(float duration) : finish_time(get_finish_time(duration))
{
}

bool 				timer::is_running() const
{
	return (float)glfwGetTime() <= finish_time;
}

bool 				timer::did_finish() const
{
	return (float)glfwGetTime() > finish_time;
}

float				timer::get_finish_time(float duration)
{
	return (float)glfwGetTime() + duration;
}