#pragma once

#include "common/aliases.h"
#include "engine/object/unique_object/unique_object.h"
#include "world/loader/file/file.h"

namespace						world
{
	class						chunk;

	class						loader;
}

class							world::loader : public engine::unique_object<loader>
{
public :
								loader();
								~loader() override;

	static bool					download(const shared_ptr<chunk> &chunk);
	static void					upload(const shared_ptr<chunk> &chunk);

private :

	enum class 					chunk_state : char
	{
		valid = 'v',
		invalid = 'i'
	};

	file						file;
};


