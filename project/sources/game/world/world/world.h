#pragma once

#include "engine/main/core/object/object/object.h"
#include "engine/main/core/object/object_constructor/unique_object_constructor/unique_object_constructor.h"
#include "engine/main/system/time/timer/timer.h"

#include "game/world/chunk/block/block_pointer/block_pointer.h"
#include "game/world/chunk/chunk/chunk/chunk.h"
#include "game/world/chunk/chunk/chunk_map/chunk_map.h"
#include "game/world/world/world_settings.h"

#include "application/common/imports/std.h"

namespace					game
{
	enum class				block_face;
	class					world;
}

class						game::world :
								public engine::object,
								public engine::unique_object_constructor<world>
{
	friend class 			block_pointer;

public :
							world();
							~world() override = default;

	static const chunk_map	&get_map();

	static block_pointer	find_block(const vec3 &position);

	static void				insert_block(const block_pointer &block, enum block_type type);
	static void				remove_block(const block_pointer &block);

	static void				select_block(const block_pointer &block, block_face face);
	static void 			unselect_block();

	static float			distance(const vec3 &position);
	static float			distance(const shared_ptr<chunk> &chunk);

	static bool				does_collide(const aabb &aabb);

private :

	chunk_map				chunks;
	vec3					pivot;

	void					when_initialized() override;
	void					when_updated() override;
	void					when_rendered() override;

	void					update_pivot();

	void					update_chunk_build(const shared_ptr<chunk> &chunk);
	void					update_chunk_visibility(const shared_ptr<chunk> &chunk);
	void					create_chunk_neighbors_if_needed(const shared_ptr<chunk> &chunk);

	void 					create_chunk_if_needed(const vec3 &position);
	void					destroy_chunk_if_needed(const shared_ptr<chunk> &chunk);

	void 					create_chunk(const vec3 &position);
	void					destroy_chunk(const shared_ptr<chunk> &chunk);
	void 					rebuild_chunk(const shared_ptr<chunk> &chunk);

	void					rebuild_chunk_and_maybe_neighbors
							(
								const shared_ptr<chunk> &chunk,
								const chunk::index &changed_block
							);

	void 					rebuild_chunk_if_exist(const vec3 &position);
};