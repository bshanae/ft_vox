#pragma once

#include "common/OpenGL.h"
#include "common/global.h"

#include "map/chunk.h"

class							chunk_generator
{
public :
								chunk_generator() = default;
	virtual						~chunk_generator() = default;

	[[nodiscard]]
	static
	block						get_block(const vec3 &position)
	{
		assert(pointer != nullptr and "Can't generate chunk");
		return (pointer->get_block_implementation(position));
	}

protected :

	static
	inline
	shared_ptr<chunk_generator>	pointer;

	[[nodiscard]]
	virtual
	block						get_block_implementation(const vec3 &position) = 0;
};