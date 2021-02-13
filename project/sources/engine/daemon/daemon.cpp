#include "daemon.h"

#include "engine/main/system/window/window.h"
#include "engine/main/system/input/input.h"
#include "engine/main/rendering/layout/layout/layout.h"
#include "engine/main/rendering/layout/layout_manager/layout_manager.h"
#include "engine/main/rendering/camera/camera/camera.h"
#include "engine/main/processor/processor.h"
#include "engine/extensions/ui/font/font_library/font_library.h"
#include "engine/extensions/ui/font/symbol/symbol_renderer.h"

using namespace		engine;

void				daemon::construct_mandatory_objects()
{
	// We need layout manager to be constructed first
	// So it tracks any object added to object_storage
	layout_manager::construct();

	window::construct();
	input::construct();

	processor::construct();
	camera::construct();

	ui::font_library::construct();
	ui::symbol_renderer::construct();
}

void				daemon::start_game_loop()
{
	processor::execute();
}