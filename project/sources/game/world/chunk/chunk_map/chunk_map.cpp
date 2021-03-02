#include "chunk_map.h"

#include "game/world/chunk/chunk/chunk.h"

using namespace			game;

void 					chunk_map::add(const shared_ptr<chunk> &chunk)
{
	lock_guard			lock{mutex_for_editing};

	emplace(chunk->get_position(), chunk);
}

void 					chunk_map::remove(const shared_ptr<chunk> &chunk)
{
	lock_guard			lock{mutex_for_editing};

	if (auto iterator = parent::find(chunk->get_position()); iterator != this->end())
		this->erase(iterator);
}

shared_ptr<chunk>		chunk_map::find(const vec3 &position) const
{
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