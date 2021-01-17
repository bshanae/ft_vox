#pragma once

#include "engine/core/object/unique_object/unique_object.h"
#include "engine/system/time/timer/timer.h"

#include "game/world/chunk/block/block_alias/block_alias.h"
#include "game/world/chunk/chunk/chunk/chunk.h"
#include "game/world/world/world_settings.h"

#include "application/common/imports/std.h"

namespace						game
{
	class						world;
}

class							game::world : public engine::unique_object<world>
{
	friend class 				block_alias;

public :
								world();
								~world() override = default;

	optional<block_alias>			find_block(const vec3 &position);

	void 						insert_block(const block_alias &id, enum block::type type);
	void 						remove_block(const block_alias &id);

	void						select_block(const block_alias &id, block::face face);
	void 						unselect_block();

	bool						does_collide(const aabb &aabb);

private :

// ----------------------------	Types

	struct						vec3_hasher
	{
		size_t					operator() (const vec3 &vector) const
		{
			size_t				h1 = hash<float>()(vector.x);
			size_t				h2 = hash<float>()(vector.y);
			size_t				h3 = hash<float>()(vector.z);

			return (h1 ^ (h2 << 1u)) ^ h3;
		}
	};

// ----------------------------	Attributes

	using						chunks_type = std::unordered_map<vec3, shared_ptr<chunk>, vec3_hasher>;

	chunks_type					chunks;

	chunks_type					new_chunks;
	vector<shared_ptr<chunk>>	old_chunks;

	using						sorted_chunks_type = multimap<float, shared_ptr<chunk>>;
	sorted_chunks_type			sorted_chunks;

	shared_mutex				map_mutex;

	engine::timer				update_timer;

// ----------------------------	Chunks

	shared_ptr<chunk>			find_chunk(const vec3 &position);
	shared_ptr<chunk>			find_new_chunk(const vec3 &position);

	shared_ptr<chunk>			find_neighbor_chunk(const shared_ptr<chunk> &main, axis axis, sign sign);

// ----------------------------	Pivot

	vec3						pivot = vec3(0.f);

	float						distance(const vec3 &position);
	float						distance(const shared_ptr<chunk> &chunk);

// ----------------------------	Object methods

	void						initialize_implementation() override;
	void						deinitialize_implementation() override;

	void						update() override;
	void						render() override;

// ----------------------------	Additional methods

	bool						create_chunk_if_needed(const vec3 &position);
	bool						destroy_chunk_if_needed(const shared_ptr<chunk> &chunk);

	void						create_chunk(const vec3 &position);
	void						destroy_chunk(const shared_ptr<chunk> &chunk);

	void 						try_build_chunk(const shared_ptr<chunk> &chunk);

	void						rebuild_chunk(const shared_ptr<chunk> &chunk, const chunk::index &changed_block);
};