#pragma once

#include "common/OpenGL.h"
#include "common/global.h"

#include "map/chunk.h"
#include "map/chunk_editor.h"

class							chunk_generator : public chunk_editor
{
public :
								chunk_generator() = default;
	virtual						~chunk_generator() = default;

	[[deprecated]]
	[[nodiscard]]
	static
	block						get_block(const vec3 &position)
	{
		assert(pointer != nullptr and "Can't generate chunk");
		return (pointer->get_block_implementation(position));
	}

	[[nodiscard]]
	static shared_ptr<chunk>	generate(const vec3 &position)
	{
		assert(pointer != nullptr and "Can't generate chunk");
		return (pointer->generate_implementation(position));
	}

protected :

	static
	inline
	shared_ptr<chunk_generator>	pointer;

	[[deprecated]]
	[[nodiscard]]
	virtual
	block						get_block_implementation(const vec3 &position) = 0;

	[[nodiscard]]
	virtual shared_ptr<chunk>	generate_implementation(const vec3 &position) = 0;
};