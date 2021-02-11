#pragma once

#include "engine/main/core/object/object/object.h"
#include "engine/main/core/object/object_constructor/unique_object_constructor/unique_object_constructor.h"
#include "engine/main/system/time/timer/timer.h"

#include "game/world/chunk/block/block_pointer/block_pointer.h"
#include "game/world/chunk/chunk/chunk/chunk.h"
#include "game/world/world/world_settings.h"

#include "application/common/imports/std.h"

namespace						game
{
	enum class					block_face;
	class						world;
}

class							game::world :
									public engine::object,
									public engine::unique_object_constructor<world>
{
	friend class 				block_pointer;

public :
								world();
								~world() override = default;

	static block_pointer		find_block(const vec3 &position);

	static shared_ptr<chunk>	find_chunk(const vec3 &position);
	static shared_ptr<chunk>	find_new_chunk(const vec3 &position);

	static void					insert_block(const block_pointer &block, enum block_type type);
	static void					remove_block(const block_pointer &block);

	static void					select_block(const block_pointer &block, block_face face);
	static void 				unselect_block();

	static bool					does_collide(const aabb &aabb);

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

	shared_ptr<chunk>			find_neighbor_chunk(const shared_ptr<chunk> &main, axis axis, sign sign);

// ----------------------------	Pivot

	vec3						pivot = vec3(0.f);

	float						distance(const vec3 &position);
	float						distance(const shared_ptr<chunk> &chunk);

// ----------------------------	Object methods

	void						when_initialized() override;

	void						when_updated() override;
	void						when_rendered() override;

// ----------------------------	Additional methods

	void						update_pivot();
	void						update_chunks_builds();
	void						destroy_far_chunks();
	void						process_new_chunks();
	void						process_old_chunks();

	bool						create_chunk_if_needed(const vec3 &position);
	bool						destroy_chunk_if_needed(const shared_ptr<chunk> &chunk);

	void						create_chunk(const vec3 &position);
	void						destroy_chunk(const shared_ptr<chunk> &chunk);

	void 						request_build(const shared_ptr<chunk> &chunk);
	void						request_rebuild(const shared_ptr<chunk> &chunk, const chunk::index &changed_block);
};