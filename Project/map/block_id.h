#pragma once

#include "chunk.h"

struct					block_id
{
	friend class		block;
	friend class		chunk;
	friend class		map;

	[[nodiscard]]
	block				&operator () () const
	{
		return (chunk->at(index));
	}

	[[nodiscard]]
	block_id			neighbor(axis axis, sign sign) const
	{
		auto			neighbor_index = index.neighbor((::axis)axis, (::sign)sign);

		if (neighbor_index)
			return (block_id(chunk, neighbor_index));
		else
			return (block_id(chunk->neighbor_block_from_another_chunk(index, axis, sign)));
	}

private :

						block_id(const shared_ptr<::chunk> &chunk, const chunk::index &index)
	{
		this->chunk = chunk;
		this->index = index;
	}

	explicit			block_id(const pair<shared_ptr<::chunk>, chunk::index> &source)
	{
		chunk = source.first;
		index = source.second;
	}

	shared_ptr<chunk>	chunk;
	chunk::index		index;
};
