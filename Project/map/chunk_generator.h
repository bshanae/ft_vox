#pragma once

#include "common/OpenGL.h"

#include "map/chunk.h"

class							chunk_generator : global<chunk_generator>
{
public :

	static
	shared_ptr<chunk_generator>	get_generator(const shared_ptr<chunk> &chunk)
	{
		auto 		instance = global<chunk_generator>::instance();

		instance->use_chunk(chunk);
		return (instance);
	}

	[[nodiscard]]
	virtual block				get_block(const chunk::index &) const = 0;

protected :

	virtual void				use_chunk(const shared_ptr<chunk> &chunk) = 0;
};