#pragma once

#include "application/common/imports/std.h"

namespace						engine
{
	class 						cubemap;
	class						cubemap_loader;
}

class							engine::cubemap_loader
{
public :
								cubemap_loader() = delete;

	static shared_ptr<cubemap>	load
								(
									const path &source_right,
									const path &source_left,
									const path &source_top,
									const path &source_bottom,
									const path &source_front,
									const path &source_back
								);
};


