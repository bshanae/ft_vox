#include "engine/daemon/daemon.h"
#include "game/daemon/daemon.h"

int					main()
{
	engine::daemon::construct_mandatory_objects();

	game::daemon::setup_layouts();
	game::daemon::construct_objects();
	game::daemon::setup_texture_atlas();

	engine::daemon::start_game_loop();

	return 0;
}