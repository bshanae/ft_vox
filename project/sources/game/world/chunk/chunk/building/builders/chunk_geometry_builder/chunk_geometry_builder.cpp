#include "chunk_geometry_builder.h"

#include "game/world/chunk/texture_atlas/texture_atlas/texture_atlas.h"
#include "game/world/chunk/block/block/block_settings.h"
#include "game/world/chunk/block/block/block.h"
#include "game/world/chunk/block/block_pointer/block_pointer.h"
#include "game/world/chunk/chunk/building/chunk_workspace/chunk_workspace.h"

#include "vertices.h"
#include "texture_coordinates.h"
#include "indices.h"
#include "occluders_offsets.h"

using namespace		game;

void				chunk_geometry_builder::launch(const shared_ptr<chunk_workspace> &workspace)
{
	debug::check_critical
	(
		workspace->state == chunk_workspace::light_done,
		"[chunk_geometry_builder] Chunk workspace has unexpected state"
	);

	workspace->state = chunk_workspace::geometry_in_process;

	workspace->batch_for_opaque.filter = &chunk_geometry_builder::filter_for_opaque;
	workspace->batch_for_opaque.geometry_future = async
	(
		launch::async,
		process_batch,
		workspace,
		ref(workspace->batch_for_opaque)
	);

	workspace->batch_for_transparent.filter = &chunk_geometry_builder::filter_for_transparent;
	workspace->batch_for_transparent.geometry_future = async
	(
		launch::async,
		process_batch,
		workspace,
		ref(workspace->batch_for_transparent)
	);

	workspace->batch_for_partially_transparent.filter = &chunk_geometry_builder::filter_for_partially_transparent;
	workspace->batch_for_partially_transparent.geometry_future = async
	(
		launch::async,
		process_batch,
		workspace,
		ref(workspace->batch_for_partially_transparent)
	);
}

void				chunk_geometry_builder::wait(const shared_ptr<chunk_workspace> &workspace)
{
	if
	(
		workspace->batch_for_opaque.geometry_future->wait_for(chrono::seconds(0)) == future_status::ready &&
		workspace->batch_for_transparent.geometry_future->wait_for(chrono::seconds(0)) == future_status::ready &&
		workspace->batch_for_partially_transparent.geometry_future->wait_for(chrono::seconds(0)) == future_status::ready
	)
	{
		workspace->state = chunk_workspace::geometry_done;

	}
}

bool				chunk_geometry_builder::filter_for_opaque(const block &block)
{
	return is_opaque(get_meta_type(block.get_type()));
}

bool				chunk_geometry_builder::filter_for_transparent(const block &block)
{
	return is_transparent(get_meta_type(block.get_type()));
}

bool				chunk_geometry_builder::filter_for_partially_transparent(const block &block)
{
	return is_partially_transparent(get_meta_type(block.get_type()));
}

void				chunk_geometry_builder::process_batch
					(
						shared_ptr<chunk_workspace> workspace,
						chunk_workspace::batch &batch
					)
{
	for (auto &iterator : *workspace->chunk)
	{
		if (batch.filter(iterator->value()))
			process_block(workspace, batch, iterator.index());
	}
}

void				chunk_geometry_builder::process_block
					(
						const shared_ptr<chunk_workspace> &workspace,
						chunk_workspace::batch &batch,
						const chunk::index &index
					)
{
	const auto		&this_block = workspace->chunk->at(index);
	const auto 		this_block_pointer = block_pointer(workspace->chunk, index);

	if (is_empty(get_meta_type((this_block.get_type()))))
		return ;

	if (is_diagonal(get_meta_type((this_block.get_type()))))
	{
		build_quad(workspace, batch, this_block, index, axis::x, sign::minus, this_block.get_light_level());
		build_quad(workspace, batch, this_block, index, axis::x, sign::plus, this_block.get_light_level());
	}
	else
	{
		for (axis axis : {axis::x, axis::y, axis::z})
		for (sign sign : {sign::minus, sign::plus})
		{
			auto	neighbor_block_pointer = this_block_pointer.get_neighbor(axis, sign);

			// If there is no neighbor block, therefore this block is end of world, so we need to draw it
			if (not neighbor_block_pointer)
				build_quad(workspace, batch, this_block, index, axis, sign, block_settings::default_light);
			else if (should_build_quad(workspace, batch, this_block_pointer, neighbor_block_pointer))
				build_quad(workspace, batch, this_block, index, axis, sign, (*neighbor_block_pointer).get_light_level());
		}
	}
}

bool				chunk_geometry_builder::should_build_quad
					(
						const shared_ptr<chunk_workspace> &workspace,
						chunk_workspace::batch &batch,
						const block_pointer &this_block_pointer,
						const block_pointer &neighbor_block_pointer
					)
{

	const auto		&this_block = *this_block_pointer;
	const auto		&neighbor_block = *neighbor_block_pointer;

	const auto		this_block_meta_type = get_meta_type(this_block.get_type());
	const auto		neighbor_block_meta_type = get_meta_type(neighbor_block.get_type());

	if (is_opaque(this_block_meta_type) and is_transparent_or_partially_transparent(neighbor_block_meta_type));
	else if (is_transparent(this_block_meta_type) and is_partially_transparent(neighbor_block_meta_type));
	else if (is_partially_transparent(this_block_meta_type) and is_partially_transparent(neighbor_block_meta_type));
	else if (is_empty(neighbor_block_meta_type));
	else
		return false;

	return true;
}

void				chunk_geometry_builder::build_quad
					(
						const shared_ptr<chunk_workspace> &workspace,
						chunk_workspace::batch &batch,
						const block &this_block,
						const chunk::index &index,
						axis axis,
						sign sign,
						float light_level
					)
{
	const auto		block_type = this_block.get_type();
	const auto		block_meta_type = get_meta_type(block_type);

	auto			texture_coordinates = ivec2(0);
	float			ao_levels[4] = {0.f, 0.f, 0.f, 0.f };

	// TODO Use block_pointer
	light_level = max(light_level, block_settings::min_light);
	block_pointer	block = block_pointer(workspace->chunk, index);

	if (axis == axis::x and sign == sign::plus)
	{
		if (is_diagonal(block_meta_type))
		{
			append_to_vector(batch.vertices, first_diagonal_vertices);
			append_to_vector(batch.texture_coordinates, first_diagonal_texture_coordinates);
		}
		else
		{
			append_to_vector(batch.vertices, right_vertices);
			append_to_vector(batch.texture_coordinates, right_texture_coordinates);
			calculate_ao_for_quad(block, right_occluders_offsets, ao_levels);
		}

		texture_coordinates = texture_atlas::get_coordinates(block_type).get_right();
	}
	else if (axis == axis::x and sign == sign::minus)
	{
		if (is_diagonal(block_meta_type))
		{
			append_to_vector(batch.vertices, second_diagonal_vertices);
			append_to_vector(batch.texture_coordinates, second_diagonal_texture_coordinates);
		}
		else
		{
			append_to_vector(batch.vertices, left_vertices);
			append_to_vector(batch.texture_coordinates, left_texture_coordinates);
			calculate_ao_for_quad(block, left_occluders_offsets, ao_levels);
		}

		texture_coordinates = texture_atlas::get_coordinates(block_type).get_left();
	}
	else if (axis == axis::y and sign == sign::plus)
	{
		append_to_vector(batch.vertices, top_vertices);
		append_to_vector(batch.texture_coordinates, top_texture_coordinates);
		texture_coordinates = texture_atlas::get_coordinates(block_type).get_top();
		calculate_ao_for_quad(block, top_occluders_offsets, ao_levels);
	}
	else if (axis == axis::y and sign == sign::minus)
	{
		append_to_vector(batch.vertices, bottom_vertices);
		append_to_vector(batch.texture_coordinates, bottom_texture_coordinates);
		texture_coordinates = texture_atlas::get_coordinates(block_type).get_bottom();
		calculate_ao_for_quad(block, bottom_occluders_offsets, ao_levels);
	}
	else if (axis == axis::z and sign == sign::plus)
	{
		append_to_vector(batch.vertices, front_vertices);
		append_to_vector(batch.texture_coordinates, front_texture_coordinates);
		texture_coordinates = texture_atlas::get_coordinates(block_type).get_front();
		calculate_ao_for_quad(block, front_occluders_offsets, ao_levels);
	}
	else if (axis == axis::z and sign == sign::minus)
	{
		append_to_vector(batch.vertices, back_vertices);
		append_to_vector(batch.texture_coordinates, back_texture_coordinates);
		texture_coordinates = texture_atlas::get_coordinates(block_type).get_back();
		calculate_ao_for_quad(block, back_occluders_offsets, ao_levels);
	}
	else
		debug::raise_error("[chunk_geometry_builder] Can't build quad");

	for (int i = (int)batch.vertices.size() - 12; i < (int)batch.vertices.size(); i += 3)
	{
		batch.vertices[i + 0] += (float)index.x;
		batch.vertices[i + 1] += (float)index.y;
		batch.vertices[i + 2] += (float)index.z;
	}

	// TODO Delegate to another method
	auto					transform_texture_coordinate = [texture_coordinates](float &x, float &y)
	{
		static vec2 		size = texture_atlas::get_texture_size();

		x = size.x * ((float)texture_coordinates.x + x);
		y = size.y * ((float)texture_coordinates.y + y);
	};

	for (int i = (int)batch.texture_coordinates.size() - 8; i < (int)batch.texture_coordinates.size(); i += 2)
		transform_texture_coordinate(batch.texture_coordinates[i + 0], batch.texture_coordinates[i + 1]);

	// TODO Delegate to another method
	const int				offset = (int)batch.indices.size() / 6 * 4;

	append_to_vector(batch.indices, indices);
	for (int i = (int)batch.indices.size() - 6; i < (int)batch.indices.size(); i++)
		batch.indices[i] += offset;

	// TODO Delegate to another method
	for (float & ao : ao_levels)
		batch.light_levels.push_back(combine_light_and_ao(light_level, ao));
}

template					<typename type>
void						chunk_geometry_builder::append_to_vector(vector<type> &target, const vector<type> &source)
{
	target.insert(target.end(), source.begin(), source.end());
}

void						chunk_geometry_builder::calculate_ao_for_quad
							(
								const block_pointer &block,
								const chunk::index (&occluders_offsets)[4][3],
								float (&ao_values)[4]
							)
{
	for (int i = 0; i < 4; i++)
		ao_values[i] = calculate_ao_for_vertex(block, occluders_offsets[i]);
}

float						chunk_geometry_builder::calculate_ao_for_vertex
							(
								const block_pointer &block,
								const chunk::index (&occluders_offsets)[3]
							)
{
	int						count = 0;
	block_pointer			neighbor_block;

	for (const auto &occluder_offset : occluders_offsets)
	{
		neighbor_block = block.get_neighbor(occluder_offset);
		count += (bool)neighbor_block and not does_transmit_light(get_meta_type(neighbor_block->get_type()));
	}

	return (float)count / 3;
}

float						chunk_geometry_builder::combine_light_and_ao(float light_level, float ao_level)
{
	static constexpr float	light_weight = 0.6f;
	static constexpr float	ao_weight = 1.f - light_weight;

	return light_level * light_weight - ao_level * light_level * ao_weight;
}