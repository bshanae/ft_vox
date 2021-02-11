#include "chunk.h"

#include "application/common/debug/defines.h"

#include "engine/main/rendering/model/model/model.h"

#include "game/world/chunk/chunk/building/chunk_build_director/chunk_build_director.h"
#include "game/world/chunk/block/block_pointer/block_pointer.h"

using namespace				game;

							chunk::chunk(const vec3 &position) :
								position(position),
								center(position + chunk_settings::size_as_vector / 2.f),
								is_built(false),
								is_visible(true)
{}

vec3						chunk::get_position() const
{
	return position;
}

vec3						chunk::get_center() const
{
	return center;
}

bool						chunk::is_valid() const
{
	return
	(
		model_for_opaque != nullptr &&
		model_for_transparent != nullptr &&
		model_for_partially_transparent != nullptr
	);
}

void						chunk::set_visible(bool state)
{
	is_visible = state;
}

void						chunk::update_build()
{
	using					build_type = optional<chunk_build_director::build>;

	shared_ptr<chunk>		pointer = shared_from_this();
	build_type				build;

	if ((build = chunk_build_director::process_build(pointer)))
	{
		model_for_opaque = build->model_for_opaque;
		model_for_transparent = build->model_for_transparent;
		model_for_partially_transparent = build->model_for_partially_transparent;
		is_built = true;
	}
}

void						chunk::update_build_if_needed()
{
	if (!is_built)
		update_build();
}

void						chunk::reset_build()
{
	const auto				pointer = shared_from_this();

	is_built = false;

#if FT_VOX_DEBUG // Makes chunk disappear if it wasn't rebuilt in one frame
	model_for_opaque = nullptr;
	model_for_transparent = nullptr;
	model_for_partially_transparent = nullptr;
#endif

	chunk_build_director::do_build_at_once(pointer);
	chunk_build_director::invalidate_build(pointer);
}