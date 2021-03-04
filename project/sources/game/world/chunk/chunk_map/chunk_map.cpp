#include "chunk_map.h"

#include "game/world/chunk/chunk/chunk.h"

using namespace			game;

void 					chunk_map::add_later(const shared_ptr<chunk> &chunk)
{
	chunk_to_add.push(chunk);
}

void 					chunk_map::remove_later(const shared_ptr<chunk> &chunk)
{
	chunk_to_remove.push(chunk);
}

void 					chunk_map::process_added_chunks()
{
	unique_lock			lock{mutex};
	shared_ptr<chunk>	new_chunk;

	while (not chunk_to_add.empty())
	{
		new_chunk = chunk_to_add.front();
		emplace(new_chunk->get_position(), new_chunk);
		chunk_to_add.pop();
	}
}

void 					chunk_map::process_removed_chunks()
{
	unique_lock			lock{mutex};

	while (not chunk_to_remove.empty())
	{
		if (auto iterator = parent::find(chunk_to_remove.front()->get_position()); iterator != this->end())
			this->erase(iterator);

		chunk_to_remove.pop();
	}
}

shared_ptr<chunk>		chunk_map::find(const vec3 &position) const
{
	shared_lock			lock{mutex};

	if (auto iterator = parent::find(position); iterator != this->cend())
		return iterator->second;
	else
		return nullptr;
}

chunk_map::iterator		chunk_map::begin()
{
	return parent::cbegin();
}
chunk_map::iterator		chunk_map::end()
{
	return parent::cend();
}

chunk_map::iterator		chunk_map::cbegin() const
{
	return parent::cbegin();
}
chunk_map::iterator		chunk_map::cend() const
{
	return parent::cend();
}