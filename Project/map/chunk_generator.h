//#pragma once
//
//#include "common/OpenGL.h"
//#include "common/global.h"
//
//#include "map/chunk.h"
//#include "map/chunk_editor.h"
//
//class							chunk_generator : public chunk_editor
//{
//public :
//								chunk_generator() = default;
//	virtual						~chunk_generator() = default;
//
//	[[deprecated]]
//	[[nodiscard]]
//	static
//	block						get_block(const vec3 &position)
//	{
//		assert(child != nullptr and "Can't generate chunk");
//		return (child->get_block_implementation(position));
//	}
//
//	[[nodiscard]]
//	static shared_ptr<chunk>	generate(const vec3 &position)
//	{
//		assert(child != nullptr and "Can't generate chunk");
//		return (child->generate_implementation(position));
//	}
//
//protected :
//
//	static
//	inline
//	shared_ptr<chunk_generator>	child;
//
//	[[deprecated]]
//	[[nodiscard]]
//	virtual
//	block						get_block_implementation(const vec3 &position) = 0;
//
//	[[nodiscard]]
//	virtual shared_ptr<chunk>	generate_implementation(const vec3 &position) = 0;
//};

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
		return (child->get_block_implementation(position));
	}

protected :

	static
	inline
	shared_ptr<chunk_generator>	child;

	[[nodiscard]]
	virtual
	block						get_block_implementation(const vec3 &position) = 0;
};
