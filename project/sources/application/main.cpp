#include "engine/launcher/launcher.h"
#include "game/launcher/launcher.h"

int					main()
{
	engine::launcher::construct_mandatory_objects();

	game::launcher::construct_engine_extension_objects();
	game::launcher::setup_layouts();
	game::launcher::construct_objects();
	game::launcher::setup_texture_atlas();

	engine::launcher::start_game_loop();

	return 0;
}