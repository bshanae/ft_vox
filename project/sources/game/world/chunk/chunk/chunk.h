#pragma once

#include "game/world/tools/array3/array3.h"
#include "game/world/block/block/block.h"
#include "game/world/chunk/chunk/chunk_settings.h"

#include "application/common/imports/opengl.h"
#include "application/common/imports/std.h"

namespace							engine
{
	class							model;
}

namespace							game
{
	class							block_ptr;
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

	inline static const vec3		left_offset = vec3(-chunk_settings::size[0], 0.f, 0.f);
	inline static const vec3		right_offset = vec3(+chunk_settings::size[0], 0.f, 0.f);
	inline static const vec3		forward_offset = vec3(0.f, 0.f, chunk_settings::size[2]);
	inline static const vec3		back_offset = vec3(0.f, 0.f, -chunk_settings::size[2]);

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
	void 							delete_build();

private :

	const vec3						position;
	const vec3						center;

	shared_ptr<engine::model>		model_for_opaque;
	shared_ptr<engine::model>		model_for_transparent;
	shared_ptr<engine::model>		model_for_partially_transparent;

	bool							is_built;
	bool							is_visible;
};