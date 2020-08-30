#pragma once

#include "common/aliases.h"
#include "engine/object/unique_object.h"
#include "world/loader/file.h"

class 							chunk;

class							loader : public unique_object<loader>
{
public :
								loader();
								~loader() override;

	static shared_ptr<chunk>	download(const vec3 &world_position);
	static void					upload(const shared_ptr<chunk> &chunk);

private :

	enum class 					chunk_state : char
	{
		valid = 'v',
		invalid = 'i'
	};

	file						file;
};


