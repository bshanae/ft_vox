#pragma once

#include "common/OpenGL.h"
#include "common/global.h"

#include "map/chunk.h"

class							chunk_casher
{
public :

	[[nodiscard]]
	static
	bool						process(shared_ptr<chunk> &chunk)
	{
		assert(pointer != nullptr and "Can't cash chunk");
		return (pointer->process_implementation(chunk));
	}

protected :

	static
	inline
	shared_ptr<chunk_casher>	pointer;

	[[nodiscard]]
	virtual
	bool						process_implementation(const shared_ptr<chunk> &chunk) = 0;
};