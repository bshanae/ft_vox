#include "map.h"

#include "application/timestamp.h"
#include "chunk_loader.h"
#include "chunk_generator.h"
#include "renderer/renderer.h"

static const vec3		left = vec3(-chunk_settings::size[0], 0.f, 0.f);
static const vec3		right = vec3(+chunk_settings::size[0], 0.f, 0.f);
static const vec3		forward = vec3(0.f, 0.f, chunk_settings::size[2]);
static const vec3		back = vec3(0.f, 0.f, -chunk_settings::size[2]);

						map::map()
{
	object_template::layout = "main";
	initial_procedure();
}

optional<block_id>		map::find_block(const vec3 &position)
{
	chunk::index		index;
	vec3				chunk_position;
	shared_ptr<chunk>	chunk;

	chunk_position.x = (int)position.x / chunk_settings::size[0];
	chunk_position.y = (int)position.y / chunk_settings::size[1];
	chunk_position.z = (int)position.z / chunk_settings::size[2];

	if (position.x < 0) chunk_position.x -= 1;
	if (position.y < 0) chunk_position.y -= 1;
	if (position.z < 0) chunk_position.z -= 1;

	chunk_position.x *= chunk_settings::size[0];
	chunk_position.y *= chunk_settings::size[1];
	chunk_position.z *= chunk_settings::size[2];

	index.x = position.x - chunk_position.x;
	index.y = position.y - chunk_position.y;
	index.z = position.z - chunk_position.z;

	if (chunk = find_chunk(chunk_position); not chunk or not index)
		return {};
	else
		return (block_id(chunk, index));
}

void					map::insert_block(const vec3 &position, enum block::type type)
{
	auto 				block = find_block(position);

	assert(block and (*block)().is_empty() and "Chunk for the block doesn't exist or block is not empty");

}

void					map::remove_block(const vec3 &position)
{

}

shared_ptr<chunk>		map::find_neighbor_chunk(const shared_ptr<chunk> &main, axis axis, sign sign)
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

shared_ptr<chunk>		map::find_chunk(const vec3 &position)
{
	auto				iterator = instance()->chunks.find(position);

	if (iterator != instance()->chunks.end())
		return (iterator->second);
	else
		return (nullptr);
}

shared_ptr<chunk>		map::find_new_chunk(const vec3 &position)
{
	auto				iterator = instance()->new_chunks.find(position);

	if (iterator != instance()->new_chunks.end())
		return (iterator->second);
	else
		return (nullptr);
}

// --------------------	Pivot

float					map::distance(const vec3 &position)
{
	return (glm::distance(pivot, position + chunk_settings::size_as_vector / 2.f));
}

float					map::distance(const shared_ptr<chunk> &chunk)
{
	return (glm::distance(pivot, (vec3)chunk->center));
}

// --------------------	Object methods

void					map::initialize_implementation()
{
	create_chunk(vec3());
	create_chunk(left);
	create_chunk(right);
	create_chunk(forward);
	create_chunk(back);
}

void					map::deinitialize_implementation()
{
	for (auto &iterator : chunks)
		chunk_loader::upload(iterator.second);
}

#include "camera/camera.h"

void					map::update()
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
		if (timestamp() - start_timestamp > map_settings::chunk_generation_time_limit)
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

		if (distance(chunk) < map_settings::visibility_limit)
			chunk->show();
		else
			chunk->hide();
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

void					map::render()
{
	for (auto [position, chunk] : chunks)
		if (chunk->main_workspace and chunk->main_workspace->model)
			renderer::render(chunk->main_workspace->model);

	for (auto [position, chunk] : chunks)
		if (chunk->water_workspace and chunk->water_workspace->model)
			sorted_models.emplace( distance(chunk), chunk->water_workspace->model);

	for (auto iterator = sorted_models.rbegin(); iterator != sorted_models.rend(); ++iterator)
		renderer::render(iterator->second);
	sorted_models.clear();
}

// -------------------- Initial procedure

void					map::initial_procedure()
{
	if (initial_procedure_context.first_call)
	{
		initial_procedure_context.first_call = false;
		initial_procedure_context.working = true;
		initial_procedure_context.target_visibility = map_settings::visibility_limit;
		map_settings::visibility_limit = initial_procedure_settings::start_visibility;
	}
	else
	{
		assert(initial_procedure_context.working);

		if (initial_procedure_context.current_visibility > map_settings::visibility_limit)
			map_settings::visibility_limit = initial_procedure_context.current_visibility;
		if (map_settings::visibility_limit >= initial_procedure_context.target_visibility)
		{
			initial_procedure_context.working = false;
			map_settings::visibility_limit = initial_procedure_context.target_visibility;
		}
	}
}

// -------------------- Additional methods

void					map::create_chunk_if_needed(const vec3 &position)
{
	if (distance(position) >= map_settings::cashing_limit)
		return ;
	if (find_chunk(position) != nullptr)
		return ;
	if (find_new_chunk(position) != nullptr)
		return ;

	find_chunk(position);
	create_chunk(position);
}

void					map::destroy_chunk_if_needed(const shared_ptr<chunk> &chunk)
{
	if (distance(chunk) >= map_settings::cashing_limit)
		destroy_chunk(chunk);
}

void					map::create_chunk(const vec3 &position)
{
	shared_ptr<chunk>	chunk;

	if (not (chunk = chunk_loader::download(position)))
		chunk = make_shared<::chunk>(position);

#warning "Generation module needed"
//	if (not (chunk = chunk_loader::download(position)))
//		chunk = chunk_generator::generate(position);

	new_chunks.emplace(position, chunk);
}

void					map::destroy_chunk(const shared_ptr<chunk> &chunk)
{
	chunk_loader::upload(chunk);
	old_chunks.push_back(chunk);
}

void 					map::try_build_chunk(const shared_ptr<chunk> &chunk)
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