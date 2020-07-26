#pragma once

#include "common/OpenGL.h"
#include "common/global.h"

#include "map/chunk.h"

class						chunk_generator
{
public :

	[[nodiscard]]
	static
	block					get_block(const vec3 &position)
	{
		return (pointer->block_getter(position));
	}

protected :

	static
	inline
	shared_ptr<chunk_generator>	pointer;

	[[nodiscard]]
	virtual
	block						block_getter(const vec3 &position) = 0;
};