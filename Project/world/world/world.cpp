#include "world.h"

#include "application/timestamp.h"
#include "world/chunk/chunk_loader.h"
#include "world/chunk/chunk_generator.h"
#include "world/chunk/chunk_renderer.h"
#include "world/chunk/highlighter.h"

static const vec3		left = vec3(-chunk_settings::size[0], 0.f, 0.f);
static const vec3		right = vec3(+chunk_settings::size[0], 0.f, 0.f);
static const vec3		forward = vec3(0.f, 0.f, chunk_settings::size[2]);
static const vec3		back = vec3(0.f, 0.f, -chunk_settings::size[2]);

						world::world()
{
	object_template::layout = "main";
	initial_procedure();
}

optional<block_id>		world::find_block(const vec3 &position)
{
	const ivec3			int_position = position;

	chunk::index		index;
	vec3				chunk_position;
	shared_ptr<chunk>	chunk;

	chunk_position.x = int_position.x / chunk_settings::size[0];
	chunk_position.y = int_position.y / chunk_settings::size[1];
	chunk_position.z = int_position.z / chunk_settings::size[2];

	if (position.x < 0 and int_position.x % chunk_settings::size[0] != 0)
		chunk_position.x -= 1;
	if (position.y < 0 and int_position.y % chunk_settings::size[1] != 0)
		chunk_position.y -= 1;
	if (position.z < 0 and int_position.z % chunk_settings::size[2] != 0)
		chunk_position.z -= 1;

	chunk_position.x *= chunk_settings::size[0];
	chunk_position.y *= chunk_settings::size[1];
	chunk_position.z *= chunk_settings::size[2];

	index.x = position.x - chunk_position.x;
	index.y = position.y - chunk_position.y;
	index.z = position.z - chunk_position.z;

	auto chunk_ = find_chunk(chunk_position);
	auto index_ = (bool)index;

	if (chunk = find_chunk(chunk_position); not chunk or not index)
		return {};
	else
		return (block_id(chunk, index));
}

void					world::insert_block(const block_id &id, enum block::type type)
{
	id().type = type;
	instance()->rebuild_chunk(id.chunk, id.index);
}

void					world::remove_block(const block_id &id)
{
	id().type = block::type::air;
	instance()->rebuild_chunk(id.chunk, id.index);
}

void					world::highlight_block(const optional<block_id> &id)
{
	if (id)
	{
		highlighter::instance()->activate();
		highlighter::instance()->model->translation = id->world_position() + vec3(0.5f);
	}
	else
		highlighter::instance()->deactivate();
}

shared_ptr<chunk>		world::find_neighbor_chunk(const shared_ptr<chunk> &main, axis axis, sign sign)
{
	vec3				neighbor_position = main->position;

	if (axis == axis::x and sign == sign::minus)
		neighbor_position += left;
	else if (axis == axis::x and sign == sign::plus)
		neighbor_position += right;
	else if (axis == axis::z and sign == sign::minus)
		neighbor_position += back;
	else if (axis == axis::z and sign == sign::plus)
		neighbor_position += forward;
	else
		return (nullptr);

	if (auto iterator = instance()->chunks.find(neighbor_position); iterator != instance()->chunks.end())
		return (iterator->second);
	else
		return (nullptr);
}

shared_ptr<chunk>		world::find_chunk(const vec3 &position)
{
	auto				iterator = instance()->chunks.find(position);

	if (iterator != instance()->chunks.end())
		return (iterator->second);
	else
		return (nullptr);
}

shared_ptr<chunk>		world::find_new_chunk(const vec3 &position)
{
	auto				iterator = instance()->new_chunks.find(position);

	if (iterator != instance()->new_chunks.end())
		return (iterator->second);
	else
		return (nullptr);
}

// --------------------	Pivot

float					world::distance(const vec3 &position)
{
	return (glm::distance(pivot, position + chunk_settings::size_as_vector / 2.f));
}

float					world::distance(const shared_ptr<chunk> &chunk)
{
	return (glm::distance(pivot, (vec3)chunk->center));
}

// --------------------	Object methods

void					world::initialize_implementation()
{
	create_chunk(vec3());
	create_chunk(left);
	create_chunk(right);
	create_chunk(forward);
	create_chunk(back);
}

void					world::deinitialize_implementation()
{
	for (auto &iterator : chunks)
		chunk_loader::upload(iterator.second);
}

#include "player/camera/camera.h"

void					world::update()
{
	auto 				try_build_chunk_if_needed = [this](const shared_ptr<chunk> &chunk)
	{
		if (chunk->build_phase != chunk::build_phase::model_done)
			try_build_chunk(chunk);
	};

	timestamp			start_timestamp;
	bool				should_postpone_build = false;

	auto				update_postpone_tasking = [start_timestamp, &should_postpone_build]()
	{
		if (timestamp() - start_timestamp > world_settings::chunk_generation_time_limit)
			should_postpone_build = true;
	};

#warning "This should be done by player"
	pivot.x = camera::position->x;
	pivot.z = camera::position->z;

	while (not chunks_with_postponed_build.empty())
	{
		auto			chunk = chunks_with_postponed_build.front();

		chunks_with_postponed_build.pop();
		try_build_chunk_if_needed(chunk);

		update_postpone_tasking();
		if (should_postpone_build)
			break ;
	}

	for (auto [position, chunk] : chunks)
	{
		create_chunk_if_needed(position + left);
		create_chunk_if_needed(position + right);
		create_chunk_if_needed(position + forward);
		create_chunk_if_needed(position + back);

		destroy_chunk_if_needed(chunk);

		if (not should_postpone_build)
		{
			update_postpone_tasking();
			try_build_chunk_if_needed(chunk);
		}
		else
			chunks_with_postponed_build.push(chunk);

		if (chunk->build_phase == chunk::build_phase::model_done)
			initial_procedure_context.current_visibility = max(initial_procedure_context.current_visibility, distance(chunk));

		chunk->is_visible = distance(chunk) < world_settings::visibility_limit;
	}

	if (initial_procedure_context.working)
		initial_procedure();

	for (auto [position, chunk] : new_chunks)
		chunks[position] = chunk;
	new_chunks.clear();

	for (auto &chunk : old_chunks)
		chunks.erase(chunk->position);
	old_chunks.clear();
}

void					world::render()
{
	for (auto [position, chunk] : chunks)
			chunk_renderer::render(chunk, chunk_renderer::mod::main);

	for (auto [position, chunk] : chunks)
			sorted_chunks.emplace(distance(chunk), chunk);

	for (auto iterator = sorted_chunks.rbegin(); iterator != sorted_chunks.rend(); ++iterator)
		chunk_renderer::render(iterator->second, chunk_renderer::mod::water);
	sorted_chunks.clear();
}

// -------------------- Initial procedure

void					world::initial_procedure()
{
	if (initial_procedure_context.first_call)
	{
		initial_procedure_context.first_call = false;
		initial_procedure_context.working = true;
		initial_procedure_context.target_visibility = world_settings::visibility_limit;
		world_settings::visibility_limit = initial_procedure_context.current_visibility;
	}
	else
	{
		assert(initial_procedure_context.working);

		if (initial_procedure_context.current_visibility > world_settings::visibility_limit)
			world_settings::visibility_limit = initial_procedure_context.current_visibility;
		if (world_settings::visibility_limit >= initial_procedure_context.target_visibility)
		{
			initial_procedure_context.working = false;
			world_settings::visibility_limit = initial_procedure_context.target_visibility;
		}
	}
}

// -------------------- Additional methods

void					world::create_chunk_if_needed(const vec3 &position)
{
	if (distance(position) >= world_settings::cashing_limit)
		return ;
	if (find_chunk(position) != nullptr)
		return ;
	if (find_new_chunk(position) != nullptr)
		return ;

	find_chunk(position);
	create_chunk(position);
}

void					world::destroy_chunk_if_needed(const shared_ptr<chunk> &chunk)
{
	if (distance(chunk) >= world_settings::cashing_limit)
		destroy_chunk(chunk);
}

void					world::create_chunk(const vec3 &position)
{
	shared_ptr<chunk>	chunk;

	if (not (chunk = chunk_loader::download(position)))
		chunk = make_shared<::chunk>(position);

#warning "Generation module needed"
//	if (not (chunk = chunk_loader::download(position)))
//		chunk = chunk_generator::generate(position);

	new_chunks.emplace(position, chunk);
}

void					world::destroy_chunk(const shared_ptr<chunk> &chunk)
{
	chunk_loader::upload(chunk);
	old_chunks.push_back(chunk);
}

void 					world::try_build_chunk(const shared_ptr<chunk> &chunk)
{
	switch (chunk->build_phase)
	{
		case (chunk::build_phase::nothing_done) :
			chunk->build(chunk::build_request::light);
			break ;

		case (chunk::build_phase::light_done) :
			if (find_chunk(*chunk->position + left) == nullptr)
				return;
			if (find_chunk(*chunk->position + right) == nullptr)
				return;
			if (find_chunk(*chunk->position + forward) == nullptr)
				return;
			if (find_chunk(*chunk->position + back) == nullptr)
				return;

			chunk->build(chunk::build_request::model);
			break ;

		default :
			assert(false and "Unexpected chunk build circumstances");
	}
}

void					world::rebuild_chunk(const shared_ptr<chunk> &chunk, const chunk::index &changed_block)
{
	static auto			find_and_rebuild = [this](const vec3 &position)
	{
		auto			chunk = find_chunk(position);

		assert(chunk);
		chunk->build(chunk::build_request::reset);
	};

	if (changed_block.x == 0)
		find_and_rebuild(*chunk->position + left);
	else if (changed_block.x == chunk_settings::size[0] - 1)
		find_and_rebuild(*chunk->position + right);

	if (changed_block.z == 0)
		find_and_rebuild(*chunk->position + back);
	else if (changed_block.z == chunk_settings::size[2] - 1)
		find_and_rebuild(*chunk->position + forward);

	chunk->build(chunk::build_request::reset);
}