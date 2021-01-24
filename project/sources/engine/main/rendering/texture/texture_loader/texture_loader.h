#pragma once

#include "engine/main/rendering/texture/texture/texture.h"

#include "application/common/imports/std.h"

namespace						engine
{
	class 						texture;
	class 						texture_loader;
}

class							engine::texture_loader
{
public :
								texture_loader() = delete;

	static shared_ptr<texture>	load(const path &source);
};


