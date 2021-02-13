#include "fps_counter.h"

using namespace		engine::utilities;

					fps_counter::fps_counter()
{
	set_layout("System");

	frames_count = 0;
	timer = engine::timer();
	last_fps = 0;
}

int					fps_counter::get_fps()
{
	return get_instance()->last_fps;
}

void 				fps_counter::when_updated()
{
	if (timer.did_finish())
	{
		last_fps = frames_count;

		timer = engine::timer(1.f);
		frames_count = 0;
	}
	else
		frames_count++;
}