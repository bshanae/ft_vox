#include "chunk_generation_controller.h"

#include "game/world/chunk/chunk/generation/chunk_workspace/chunk_workspace.h"
#include "game/world/chunk/chunk/generation/generators/chunk_landscape_generator/chunk_landscape_generator/chunk_landscape_generator.h"
#include "game/world/chunk/chunk/generation/generators/chunk_light_generator/chunk_light_generator.h"
#include "game/world/chunk/chunk/generation/generators/chunk_geometry_generator/chunk_geometry_generator/chunk_geometry_generator.h"
#include "game/world/chunk/chunk/generation/generators/chunk_model_generator/chunk_model_generator.h"
#include "game/world/world/world.h"

using namespace					game;

using							build_type = chunk_build_director::build;

								chunk_build_director::chunk_build_director()
{
	set_layout("System");

	chunk_landscape_generator::construct();
	chunk_light_generator::construct();
	chunk_geometry_generator::construct();
	chunk_model_generator::construct();
}

optional<build_type>			chunk_build_director::process_build(const shared_ptr<chunk> &chunk)
{
	auto 						instance = get_instance();
	shared_ptr<chunk_workspace>	workspace = instance->get_or_create_workspace(chunk);

	engine::timer				timer(10 / 60.f);

	if (instance->get_state() == state::deinitialized)
		return nullopt;

	while (true)
	{
		if (timer.did_finish())
			break;

		switch (workspace->state)
		{
			case chunk_workspace::nothing_done:
				log_requesting_landscape(chunk);
				chunk_landscape_generator::process(workspace);
				break;;

			case chunk_workspace::landscape_done:
				log_requesting_light_build(chunk);
				chunk_light_generator::process(workspace);
				break;

			case chunk_workspace::light_done:
				if (are_all_neighbors_present_and_have_light(chunk))
				{
					log_requesting_geometry_build(chunk);
					chunk_geometry_generator::process(workspace);
				}
				break;

			case chunk_workspace::geometry_in_process:
				chunk_geometry_generator::wait(workspace);
				break;

			case chunk_workspace::geometry_done:
				log_requesting_model_build(chunk);
				chunk_model_generator::process(workspace);
				break;

			case chunk_workspace::model_done:
				workspace->build_at_once = false;
				return optional<chunk_build_director::build>(package_build(workspace));

			case chunk_workspace::landscape_in_process:
			case chunk_workspace::light_in_process:
			case chunk_workspace::model_in_process:
				break;
		}

		if (not workspace->build_at_once)
			break;
	}

	// If we can't build workspace in one frame, that means that, neighbor chunks are not ready
	// So we shouldn't try to build the chunk
	workspace->build_at_once = false;

	return nullopt;
}

void							chunk_build_director::invalidate_build(const shared_ptr<chunk> &chunk)
{
	if (auto workspace = get_instance()->get_workspace(chunk); workspace != nullptr)
		workspace->reset();
}
void							chunk_build_director::do_build_at_once(const shared_ptr<chunk> &chunk)
{
	if (get_instance()->get_state() == state::deinitialized)
		return;

	get_instance()->get_or_create_workspace(chunk)->build_at_once = true;
}

void 							chunk_build_director::when_deinitialized()
{
	auto 						instance = get_instance();

#if !FT_VOX_FORCE_EXIT
	for (auto iterator = instance->data.cbegin(); iterator != instance->data.cend();)
	{
		iterator->second->wait();
		instance->data.erase(iterator++);
	}
#endif
}

shared_ptr<chunk_workspace>		chunk_build_director::get_workspace(const shared_ptr<chunk> &chunk) const
{
	if (!data.contains(chunk))
		return nullptr;

	return data.at(chunk);
}

shared_ptr<chunk_workspace>		chunk_build_director::get_or_create_workspace(const shared_ptr<chunk> &chunk)
{
	if (!data.contains(chunk))
		data.emplace(chunk, make_shared<chunk_workspace>(chunk));

	return data.at(chunk);
}

build_type						chunk_build_director::package_build(const shared_ptr<chunk_workspace> &workspace)
{
	return build
	{
		.model_for_opaque = workspace->batch_for_opaque.model,
		.model_for_transparent = workspace->batch_for_transparent.model,
		.model_for_partially_transparent = workspace->batch_for_partially_transparent.model
	};
}

bool							chunk_build_director::is_chunk_present_and_has_light(const vec3 &position)
{
	shared_ptr<chunk>			chunk;
	shared_ptr<chunk_workspace>	workspace;

	chunk = world::find_chunk(position);
	if (chunk == nullptr)
		return false;

	workspace = get_instance()->get_workspace(chunk);
	if (workspace == nullptr)
		return false;

	return workspace->state >= chunk_workspace::light_done;
}

bool							chunk_build_director::are_all_neighbors_present_and_have_light(const shared_ptr<chunk> &chunk)
{
	static const vec3			left = vec3(-chunk_settings::size[0], 0.f, 0.f);
	static const vec3			right = vec3(+chunk_settings::size[0], 0.f, 0.f);
	static const vec3			forward = vec3(0.f, 0.f, chunk_settings::size[2]);
	static const vec3			back = vec3(0.f, 0.f, -chunk_settings::size[2]);

	return
	(
		is_chunk_present_and_has_light(chunk->get_position() + left) and
		is_chunk_present_and_has_light(chunk->get_position() + right) and
		is_chunk_present_and_has_light(chunk->get_position() + forward) and
		is_chunk_present_and_has_light(chunk->get_position() + back)
	);
}

void							chunk_build_director::log_requesting_landscape(const shared_ptr<chunk> &chunk)
{
	debug::log("[chunk_build_director] Requesting landscape for chunk at " + to_string(chunk->get_position()));
}

void							chunk_build_director::log_requesting_light_build(const shared_ptr<chunk> &chunk)
{
	debug::log("[chunk_build_director] Requesting light build for chunk at " + to_string(chunk->get_position()));
}

void							chunk_build_director::log_requesting_geometry_build(const shared_ptr<chunk> &chunk)
{
	debug::log("[chunk_build_director] Requesting geometry build for chunk at " + to_string(chunk->get_position()));
}

void							chunk_build_director::log_requesting_model_build(const shared_ptr<chunk> &chunk)
{
	debug::log("[chunk_build_director] Requesting model build for chunk at " + to_string(chunk->get_position()));
}