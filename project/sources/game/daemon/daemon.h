#pragma once

namespace			game
{
	class 			daemon;
}

class				game::daemon
{
public :

	static void 	construct_engine_extension_objects();
	static void 	setup_layouts();
	static void 	construct_objects();
	static void 	setup_texture_atlas();
};