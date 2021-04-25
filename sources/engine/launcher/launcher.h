#pragma once

namespace			engine
{
	class 			launcher;
}

class				engine::launcher
{
public :

	static void 	construct_mandatory_objects();
	static void 	start_game_loop();
};