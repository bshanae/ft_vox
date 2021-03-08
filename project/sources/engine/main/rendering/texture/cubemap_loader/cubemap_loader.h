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
									const string &source_right,
									const string &source_left,
									const string &source_top,
									const string &source_bottom,
									const string &source_front,
									const string &source_back
								);
};


