#pragma once

#include "application/common/imports/std.h"
#include "application/common/imports/glm.h"

namespace						game
{
	class 						chunk;
	class 						chunk_map;
}

struct							vec3_hasher
{
	size_t						operator() (const vec3 &vector) const
	{
		size_t					hash_x = hash<float>()(vector.x);
		size_t					hash_y = hash<float>()(vector.y);
		size_t					hash_z = hash<float>()(vector.z);

		return (hash_x ^ (hash_y << 1u)) ^ hash_z;
	}
};

class							game::chunk_map : private unordered_map<vec3, shared_ptr<chunk>, vec3_hasher>
{
	using						parent = unordered_map<vec3, shared_ptr<chunk>, vec3_hasher>;
	using						iterator = parent::const_iterator;

public :

	void 						add_later(const shared_ptr<chunk> &chunk);
	void 						remove_later(const shared_ptr<chunk> &chunk);

	void 						process_added_chunks();
	void 						process_removed_chunks();

	shared_ptr<chunk>			find(const vec3 &position) const;

	iterator					begin();
	iterator					end();

	iterator					cbegin() const;
	iterator					cend() const;

private :

	queue<shared_ptr<chunk>>	chunk_to_add;
	queue<shared_ptr<chunk>>	chunk_to_remove;

	mutable shared_mutex		mutex;
};