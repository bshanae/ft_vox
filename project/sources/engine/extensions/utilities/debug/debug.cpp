#include "debug.h"

using namespace		engine;

					utilities::debug::debug() :
						total_frames_count(0),
						start_timestamp()
{
	set_layout("System");
}

void 				utilities::debug::when_updated()
{
	total_frames_count++;

	if constexpr (print_average_fps)
		cerr << "\r" << to_string(get_average_fps()) << std::flush;

	if constexpr (exit_after_some_time)
	{
		if (timestamp() - start_timestamp > exit_time)
			exit(2);
	}
}

float				utilities::debug::get_average_fps()
{
	return (float)total_frames_count / (timestamp() - start_timestamp);
}