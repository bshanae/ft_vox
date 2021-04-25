#pragma once

namespace			game
{
	class 			launcher;
}

class				game::launcher
{
public :

	static void 	setup_layouts();
	static void 	construct_engine_extension_objects();
	static void 	construct_game_objects();
	static void 	setup_texture_atlas();
	static void 	setup_biomes();
	static void 	construct_player();
};