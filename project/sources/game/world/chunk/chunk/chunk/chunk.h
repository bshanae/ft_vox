#pragma once

#include "game/world/tools/array3/array3.h"
#include "game/world/chunk/block/block/block.h"
#include "game/world/chunk/block/block_pointer/block_pointer.h"
#include "game/world/chunk/chunk/chunk/chunk_settings.h"

#include "application/common/imports/opengl.h"
#include "application/common/imports/std.h"

namespace							engine
{
	class							model;
}

namespace							game
{
	class							block_pointer;
	class							world;

	class							chunk_workspace;
	class							chunk_renderer;
	class							chunk;
}

class								game::chunk :
										public chunk_settings::underlying_array,
										public enable_shared_from_this<chunk>
{
	friend class 					chunk_renderer;

public :

	using							index = array3<block, chunk_settings::size[0], chunk_settings::size[1], chunk_settings::size[2]>::index;

public :

	explicit						chunk(const vec3 &position);
									~chunk() override = default;

	vec3							get_position() const;
	vec3							get_center() const;

	bool							is_valid() const;

	void							set_visible(bool state);

	void							update_build();
	void							update_build_if_needed();
	void							reset_build();

private :

	const vec3						position;
	const vec3						center;

	shared_ptr<engine::model>		model_for_opaque;
	shared_ptr<engine::model>		model_for_transparent;
	shared_ptr<engine::model>		model_for_partially_transparent;

	bool							is_built;
	bool							is_visible;
};