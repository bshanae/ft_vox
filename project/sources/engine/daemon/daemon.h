#pragma once

namespace			engine
{
	class 			daemon;
}

class				engine::daemon
{
public :

	static void 	construct_mandatory_objects();
	static void 	start_game_loop();
};