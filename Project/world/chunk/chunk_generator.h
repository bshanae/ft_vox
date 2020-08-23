#pragma once

#include "common/OpenGL.h"
#include "common/global.h"
#include "world/chunk/chunk.h"

class							chunk_generator
{
public :
								chunk_generator() = default;
	virtual						~chunk_generator() = default;

	static shared_ptr<chunk>	generate(const vec3 &position)
	{
		assert(pointer != nullptr and "Can't generate chunk");
		return (pointer->generate_implementation(position));
	}

protected :

	static
	inline
	shared_ptr<chunk_generator>	pointer;

	virtual shared_ptr<chunk>	generate_implementation(const vec3 &position) = 0;
};