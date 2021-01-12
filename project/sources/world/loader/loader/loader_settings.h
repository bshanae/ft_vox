#pragma once

#include "common/aliases.h"
#include "world/loader/file/file.h"
#include "engine/object/unique_object/unique_object.h"

namespace						world
{
	struct						loader_settings;
}
struct							world::loader_settings
{
	static inline int 			chunk_linear_size = chunk_settings::size[0] * chunk_settings::size[1] * chunk_settings::size[2];

	static inline const string	path_to_file = "Project/resources/profiles/main.vox";
	static inline const string	header = "Vox";
};
