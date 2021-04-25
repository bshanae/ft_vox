#include "chunk_geometry_generation_task.h"

#include "game/world/texture_atlas/texture_atlas/texture_atlas.h"
#include "game/world/block/block/block_settings.h"

#include "game/world/chunk/generation/chunk_generation_task/chunk_geometry_generation_task/data/vertices.h"
#include "game/world/chunk/generation/chunk_generation_task/chunk_geometry_generation_task/data/texture_coordinates.h"
#include "game/world/chunk/generation/chunk_generation_task/chunk_geometry_generation_task/data/indices.h"
#include "game/world/chunk/generation/chunk_generation_task/chunk_geometry_generation_task/tools/vector_tools/vector_tools.h"
#include "game/world/chunk/generation/chunk_generation_task/chunk_geometry_generation_task/tools/ao_calculator/ao_calculator.h"
#include "game/world/chunk/generation/chunk_generation_task/chunk_geometry_generation_task/tools/light_mixer/light_mixer.h"

using namespace		game;

					chunk_geometry_generation_task::chunk_geometry_generation_task() : chunk_generation_task(true)
{}

void 				chunk_geometry_generation_task::do_launch(chunk_workspace &workspace)
{
	filter_blocks_and_save_to_batches(workspace);
	launch_batches_processing(workspace);
}

void				chunk_geometry_generation_task::filter_blocks_and_save_to_batches(chunk_workspace &workspace)
{
	for (auto &iterator : *workspace.chunk)
	{
		const auto	block = block_ptr(workspace.chunk, iterator->get_index());
		const auto	block_meta_type = get_meta_type(block->get_type());

		if (is_empty(block_meta_type))
			;
		else if (is_opaque(block_meta_type))
			workspace.batch_for_opaque.blocks.push_back(block);
		else if (is_transparent(block_meta_type))
			workspace.batch_for_transparent.blocks.push_back(block);
		else if (is_partially_transparent(block_meta_type))
			workspace.batch_for_partially_transparent.blocks.push_back(block);
		else
			debug::raise_error("[game::chunk_geometry_generation_task] Unexpected code branch");
	}
}

void 				chunk_geometry_generation_task::launch_batches_processing(chunk_workspace &workspace)
{
	process_batch(workspace.batch_for_opaque);
	process_batch(workspace.batch_for_transparent);
	process_batch(workspace.batch_for_partially_transparent);
}

void				chunk_geometry_generation_task::process_batch(chunk_workspace::batch &batch)
{
	for (const auto &block : batch.blocks)
		process_block(batch, block);
}

void				chunk_geometry_generation_task::process_block(chunk_workspace::batch &batch, const block_ptr &block)
{
	if (is_empty(get_meta_type((block->get_type()))))
		return ;

	if (is_diagonal(get_meta_type((block->get_type()))))
	{
		generate_quad(batch, block, block_face::left, block->get_light_level());
		generate_quad(batch, block, block_face::right, block->get_light_level());
	}
	else
	{
		for (block_face face : get_all_block_faces())
		{
			if (auto neighbor_block = block.get_neighbor(face); neighbor_block)
			{
				if (should_generate_quad(batch, block, neighbor_block))
					generate_quad(batch, block, face, neighbor_block->get_light_level());
			}
			else
			{
				// If there is no neighbor block, therefore this block is end of world, so we need to draw it
				generate_quad(batch, block, face, block_settings::default_light_level);
			}
		}
	}
}

bool				chunk_geometry_generation_task::should_generate_quad(chunk_workspace::batch &batch, const block_ptr &this_block, const block_ptr &neighbor_block)
{
	const auto		this_block_meta_type = get_meta_type(this_block->get_type());
	const auto		neighbor_block_meta_type = get_meta_type(neighbor_block->get_type());

	if (is_opaque(this_block_meta_type) and is_transparent_or_partially_transparent(neighbor_block_meta_type));
	else if (is_transparent(this_block_meta_type) and is_partially_transparent(neighbor_block_meta_type));
	else if (is_partially_transparent(this_block_meta_type) and is_partially_transparent(neighbor_block_meta_type));
	else if (is_empty(neighbor_block_meta_type));
	else
		return false;

	return true;
}

void 				chunk_geometry_generation_task::generate_quad(chunk_workspace::batch &batch, const block_ptr &block, block_face face, float light_level)
{
	generate_indices(batch);
	generate_vertices(batch, block, face);
	generate_texture_coordinates(batch, block, face);
	generate_light_levels(batch, block, face, light_level);
}

void				chunk_geometry_generation_task::generate_indices(chunk_workspace::batch &batch)
{
	const int		offset = (int)batch.indices.size() / 6 * 4;

	vector_tools::append(batch.indices, indices);
	for (int i = (int)batch.indices.size() - 6; i < (int)batch.indices.size(); i++)
		batch.indices[i] += offset;
}

void				chunk_geometry_generation_task::generate_vertices(chunk_workspace::batch &batch, const block_ptr &block, block_face face)
{
	const auto		block_type = block->get_type();
	const auto		block_meta_type = get_meta_type(block_type);

	if (face == block_face::right)
	{
		if (is_diagonal(block_meta_type))
		{
			vector_tools::append(batch.vertices, first_diagonal_vertices);
			vector_tools::append(batch.texture_coordinates, first_diagonal_texture_coordinates);
		}
		else
		{
			vector_tools::append(batch.vertices, right_vertices);
			vector_tools::append(batch.texture_coordinates, right_texture_coordinates);
		}
	}
	else if (face == block_face::left)
	{
		if (is_diagonal(block_meta_type))
		{
			vector_tools::append(batch.vertices, second_diagonal_vertices);
			vector_tools::append(batch.texture_coordinates, second_diagonal_texture_coordinates);
		}
		else
		{
			vector_tools::append(batch.vertices, left_vertices);
			vector_tools::append(batch.texture_coordinates, left_texture_coordinates);
		}
	}
	else if (face == block_face::top)
	{
		vector_tools::append(batch.vertices, top_vertices);
		vector_tools::append(batch.texture_coordinates, top_texture_coordinates);
	}
	else if (face == block_face::bottom)
	{
		vector_tools::append(batch.vertices, bottom_vertices);
		vector_tools::append(batch.texture_coordinates, bottom_texture_coordinates);
	}
	else if (face == block_face::front)
	{
		vector_tools::append(batch.vertices, front_vertices);
		vector_tools::append(batch.texture_coordinates, front_texture_coordinates);
	}
	else if (face == block_face::back)
	{
		vector_tools::append(batch.vertices, back_vertices);
		vector_tools::append(batch.texture_coordinates, back_texture_coordinates);
	}
	else
		debug::raise_error("[game::chunk_geometry_builder] Can't generate vertices");

	for (int i = (int)batch.vertices.size() - 12; i < (int)batch.vertices.size(); i += 3)
	{
		batch.vertices[i + 0] += (float)block.get_index().x;
		batch.vertices[i + 1] += (float)block.get_index().y;
		batch.vertices[i + 2] += (float)block.get_index().z;
	}

}

void				chunk_geometry_generation_task::generate_texture_coordinates(chunk_workspace::batch &batch, const block_ptr &block, block_face face)
{
	static const
	auto			transform_texture_coordinate = [](const ivec2 &texture_coordinates, float &x, float &y)
	{
		static const
		vec2		size = texture_atlas::get_texture_size();

		x = size.x * ((float)texture_coordinates.x + x);
		y = size.y * ((float)texture_coordinates.y + y);
	};

	auto					texture_coordinates = ivec2(0);

	switch (face)
	{
		case block_face::right:
			texture_coordinates = texture_atlas::get_coordinates(block->get_type()).get_right();
			break;

		case block_face::left:
			texture_coordinates = texture_atlas::get_coordinates(block->get_type()).get_left();
			break;

		case block_face::top:
			texture_coordinates = texture_atlas::get_coordinates(block->get_type()).get_top();
			break;

		case block_face::bottom:
			texture_coordinates = texture_atlas::get_coordinates(block->get_type()).get_bottom();
			break;

		case block_face::front:
			texture_coordinates = texture_atlas::get_coordinates(block->get_type()).get_front();
			break;

		case block_face::back:
			texture_coordinates = texture_atlas::get_coordinates(block->get_type()).get_back();
			break;

		default :
			debug::raise_error("[game::chunk_geometry_builder] Can't generate texture coordinates");
	}

	for (int i = (int)batch.texture_coordinates.size() - 8; i < (int)batch.texture_coordinates.size(); i += 2)
		transform_texture_coordinate(texture_coordinates, batch.texture_coordinates[i + 0], batch.texture_coordinates[i + 1]);
}

void 				chunk_geometry_generation_task::generate_light_levels(chunk_workspace::batch &batch, const block_ptr &block, block_face face, float light_level)
{
	light_level = clamp(light_level, block_settings::min_light_level, block_settings::max_light_level);

	for (float &ao : ao_calculator::calculate(block, face))
		batch.light_levels.push_back(light_mixer::mix_light_and_ao(light_level, ao));
}