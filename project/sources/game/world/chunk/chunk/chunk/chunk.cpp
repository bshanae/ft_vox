#include "chunk.h"

#include "engine/main/rendering/model/model/model.h"

#include "game/world/chunk/texture_atlas/texture_atlas.h"
#include "game/world/chunk/block/block/block_settings.h"

#include "application/common/imports/std.h"

using namespace			game;

static const float		epsilon = 0.005f;

static vector<GLfloat>	front_vertices =
{
	+0.5f, +0.5f, +0.5f,
	-0.5f, +0.5f, +0.5f,
	-0.5f, -0.5f, +0.5f,
	+0.5f, -0.5f, +0.5f
};

static vector<GLfloat>	front_texture_coordinates =
{
	1.f - epsilon, 1.f - epsilon,
	0.f + epsilon, 1.f - epsilon,
	0.f + epsilon, 0.f + epsilon,
	1.f - epsilon, 0.f + epsilon,
};

static vector<GLfloat>	back_vertices =
{
	+0.5f, +0.5f, -0.5f,
	+0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, +0.5f, -0.5f
};

static vector<GLfloat>	back_texture_coordinates =
{
	0.f + epsilon, 1.f - epsilon,
	0.f + epsilon, 0.f + epsilon,
	1.f - epsilon, 0.f + epsilon,
	1.f - epsilon, 1.f - epsilon,
};

static vector<GLfloat>	top_vertices =
{
	-0.5f, +0.5f, +0.5f,
	+0.5f, +0.5f, +0.5f,
	+0.5f, +0.5f, -0.5f,
	-0.5f, +0.5f, -0.5f
};

static vector<GLfloat>	top_texture_coordinates =
{
	0.f + epsilon, 0.f + epsilon,
	1.f - epsilon, 0.f + epsilon,
	1.f - epsilon, 1.f - epsilon,
	0.f + epsilon, 1.f - epsilon,
};

static vector<GLfloat>	bottom_vertices =
{
	-0.5f, -0.5f, +0.5f,
	-0.5f, -0.5f, -0.5f,
	+0.5f, -0.5f, -0.5f,
	+0.5f, -0.5f, +0.5f
};

static vector<GLfloat>	bottom_texture_coordinates =
{
	0.f + epsilon, 0.f + epsilon,
	0.f + epsilon, 1.f - epsilon,
	1.f - epsilon, 1.f - epsilon,
	1.f - epsilon, 0.f + epsilon,
};

static vector<GLfloat>	right_vertices =
{
	+0.5f, +0.5f, +0.5f,
	+0.5f, -0.5f, +0.5f,
	+0.5f, -0.5f, -0.5f,
	+0.5f, +0.5f, -0.5f
};

static vector<GLfloat>	right_texture_coordinates =
{
	0.f + epsilon, 1.f - epsilon,
	0.f + epsilon, 0.f + epsilon,
	1.f - epsilon, 0.f + epsilon,
	1.f - epsilon, 1.f - epsilon,
};

static vector<GLfloat>	left_vertices =
{
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, +0.5f,
	-0.5f, +0.5f, +0.5f,
	-0.5f, +0.5f, -0.5f,
};

static vector<GLfloat>	left_texture_coordinates =
{
	0.f + epsilon, 0.f + epsilon,
	1.f - epsilon, 0.f + epsilon,
	1.f - epsilon, 1.f - epsilon,
	0.f + epsilon, 1.f - epsilon
};

static vector<GLfloat>	first_diagonal_vertices =
{
	+0.5f, +0.5f, +0.5f,
	-0.5f, +0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	+0.5f, -0.5f, +0.5f,
};

static vector<GLfloat>	first_diagonal_texture_coordinates =
{
	1.f - epsilon, 1.f - epsilon,
	0.f + epsilon, 1.f - epsilon,
	0.f + epsilon, 0.f + epsilon,
	1.f - epsilon, 0.f + epsilon,
};

static vector<GLfloat>	second_diagonal_vertices =
{
	+0.5f, +0.5f, -0.5f,
	-0.5f, +0.5f, +0.5f,
	-0.5f, -0.5f, +0.5f,
	+0.5f, -0.5f, -0.5f,
};

static vector<GLfloat>	second_diagonal_texture_coordinates =
{
	1.f - epsilon, 1.f - epsilon,
	0.f + epsilon, 1.f - epsilon,
	0.f + epsilon, 0.f + epsilon,
	1.f - epsilon, 0.f + epsilon,
};

static vector<GLuint>	indices =
{
	0, 1, 3,
	1, 2, 3
};

						chunk::chunk(const vec3 &position) :
							position(position),
							center(position + chunk_settings::size_as_vector / 2.f)
{
	workspace_for_opaque.predicate = [](block &block){ return (block.is_opaque()); };
	workspace_for_transparent.predicate = [](block &block){ return (block.is_transparent()); };
	workspace_for_partially_transparent.predicate = [](block &block){ return (block.is_partially_transparent()); };
}

vec3					chunk::get_position() const
{
	return position;
}

vec3					chunk::get_center() const
{
	return center;
}

// -------------------- Build functions

std::thread::id			main_thread;

void					chunk::build(build_request request)
{
	main_thread = this_thread::get_id();

	switch (request)
	{
		case (build_request::reset) :
			build_phase = build_phase::nothing_done;
			break ;

		case (build_request::light) :
			build_phase = build_phase::light_in_process;
			light_build_status = async(launch::async, &chunk::build_light, this);
			break ;

		case (build_request::geometry) :
			assert(build_phase == build_phase::light_done);
			build_phase = build_phase::geometry_in_process;

			workspace_for_opaque.geometry_build_status = async(launch::async, &chunk::build_geometry, this, ref(workspace_for_opaque));
			workspace_for_transparent.geometry_build_status = async(launch::async, &chunk::build_geometry, this, ref(workspace_for_transparent));
			workspace_for_partially_transparent.geometry_build_status = async(launch::async, &chunk::build_geometry, this, ref(workspace_for_partially_transparent));
			break ;

		case (build_request::model) :
			assert(build_phase == build_phase::geometry_done and "Unexpected build phase");
			build_model(workspace_for_opaque);
			build_model(workspace_for_transparent);
			build_model(workspace_for_partially_transparent);
			build_phase = build_phase::model_done;
			break ;

		default :
			assert(0);
	}
}

void					chunk::wait(build_request request)
{
	switch (request)
	{
		case (build_request::reset) :
			build_phase = build_phase::nothing_done;
			break ;

		case (build_request::light) :
			if (light_build_status.wait_for(chrono::seconds(0)) == future_status::ready)
				build_phase = build_phase::light_done;
			break ;

		case (build_request::geometry) :
			assert(build_phase == build_phase::geometry_in_process);

			bool is_opaque_ready;
			bool is_transparent_ready;
			bool is_partially_transparent_ready;

			is_opaque_ready = workspace_for_opaque.geometry_build_status.wait_for(chrono::seconds(0)) == future_status::ready;
			is_transparent_ready = workspace_for_transparent.geometry_build_status.wait_for(chrono::seconds(0)) == future_status::ready;
			is_partially_transparent_ready = workspace_for_partially_transparent.geometry_build_status.wait_for(chrono::seconds(0)) == future_status::ready;

			if (is_opaque_ready and is_transparent_ready and is_partially_transparent_ready)
				build_phase = build_phase::geometry_done;
			break ;

		default :
			assert(0);
	}
}

void					chunk::build_light()
{
	queue<index>		queue;

	chunk::index		index;
	chunk::index		neighbor_index;

	index.y = chunk_settings::size[1] - 1;
	for (index.x = 0; index.x < chunk_settings::size[0]; index.x++)
		for (index.z = 0; index.z < chunk_settings::size[2]; index.z++)
		{
			at(index).light_level = block_settings::sun_light_level;
			queue.push(index);
		}

	while (not queue.empty())
	{
		index = queue.front();
		queue.pop();

		if (neighbor_index = index.get_neighbor(axis::y, sign::minus); not neighbor_index)
			continue ;
		if (not at(neighbor_index).does_transmit_light())
			continue ;
		if (at(index).light_level - at(neighbor_index).light_level >= 2)
		{
			at(neighbor_index).light_level = (char)(at(index).light_level);
			queue.push(neighbor_index);
		}
	}
}

void					chunk::build_geometry(batch_workspace &workspace)
{
	workspace.vertices.clear();
	workspace.texture_coordinates.clear();
	workspace.light_levels.clear();
	workspace.indices.clear();

	for (auto &iterator : *this)
	{
		if (workspace.predicate(iterator->value()))
			build_block(workspace, iterator.index());
	}
}

void					chunk::build_model(batch_workspace &workspace)
{
	workspace.model = make_shared<engine::model>();

//	vec3(0.5f) is block offset, so first block is on vec3(0, 0, 0)
	workspace.model->set_translation((vec3)position + vec3(0.5f));
	workspace.model->bind(true);

	workspace.model->add_vbo(3, workspace.vertices);
	workspace.model->add_vbo(2, workspace.texture_coordinates);
	workspace.model->add_vbo(1, workspace.light_levels);
	workspace.model->add_ebo(workspace.indices);

	workspace.model->bind(false);
}

// -------------------- Build helpers

float					chunk::calculate_ao(const index &index, axis axis, sign sign)
{
	optional<block_alias>	central_neighbor;

	central_neighbor = block_alias(shared_from_this(), index).get_neighbor(axis, sign);
	if (not central_neighbor)
		return (0.f);

	int					occluders_count = 0;
	const int 			occluders_max_count = 8 * 2;

	optional<block_alias>	occluder;
	for (int first_axis = (int)axis::x; first_axis <= (int)axis::z; first_axis++)
	{
		if ((::axis)first_axis == axis)
			continue ;

		for (int second_axis = (int)axis::x; second_axis <= (int)axis::z; second_axis++)
		{
			if ((::axis)second_axis == axis)
				continue ;
			if (first_axis == second_axis)
				continue ;

			for (int first_sign = -1; first_sign <= 1; first_sign++)
				for (int second_sign = -1; second_sign <= 1; second_sign++)
				{
					if (first_sign == 0 and second_sign == 0)
						continue ;

					occluder = central_neighbor;
					if (first_sign != 0)
						occluder = occluder->get_neighbor((::axis)first_axis, (::sign)first_sign);
					if (second_sign != 0 and occluder)
						occluder = occluder->get_neighbor((::axis)second_axis, (::sign)second_sign);

					if (occluder and not (*occluder)().does_transmit_light())
					{
						if (first_sign == 0 or second_sign == 0)
							occluders_count += 2;
						else
							occluders_count += 1;
					}
				}
		}
	}

	return ((float)occluders_count / occluders_max_count);
}

char					chunk::apply_ao(char light_level, float ao)
{
	const char			dynamic_part = (float)light_level * 0.4f;
	const char			static_part = light_level - dynamic_part;

	const char			ao_result = (float)dynamic_part * (1.f - ao);

	return (static_part + ao_result);
}

void					chunk::build_block(batch_workspace &workspace, const index &index)
{
	auto 				try_build_quad = [this, &workspace, index](axis axis, sign sign)
	{
		auto			this_block_id = block_alias(shared_from_this(), index);
		auto 			neighbor_block_id = this_block_id.get_neighbor(axis, sign);

		if (neighbor_block_id)
		{
			auto 		this_block = this_block_id();
			auto 		neighbor_block = (*neighbor_block_id)();

			if (this_block.is_opaque() and neighbor_block.is_transparent_or_partially_transparent());
			else if (this_block.is_transparent() and neighbor_block.is_partially_transparent());
			else if (this_block.is_partially_transparent() and neighbor_block.is_partially_transparent());
			else if (neighbor_block.is_empty());
			else
				return ;

			auto		ao = calculate_ao(index, axis, sign);
			auto		light_level = apply_ao(neighbor_block.light_level, ao);

			build_quad(workspace, index, (::axis)axis, (::sign)sign, light_level);
		}
		else if (not neighbor_block_id)
			build_quad(workspace, index, (::axis)axis, (::sign)sign, block_settings::default_light_level);
	};

	auto				&this_block = at(index);

	if (this_block.is_empty())
		return ;

	if (this_block.is_diagonal())
	{
		build_quad(workspace, index, axis::x, sign::minus, this_block.light_level - 1);
		build_quad(workspace, index, axis::x, sign::plus, this_block.light_level - 1);
	}
	else
	{
		for (int axis = (int)axis::x; axis <= (int)axis::z; axis++)
		{
			try_build_quad((::axis)axis, sign::minus);
			try_build_quad((::axis)axis, sign::plus);
		}
	}
}

template				<typename type>
void					append_to_vector(vector<type> &target, const vector<type> &source)
{
	target.insert(target.end(), source.begin(), source.end());
}

void					chunk::build_quad(
							batch_workspace &workspace,
							const index &index,
							axis axis,
							sign sign,
							char light_level)
{
	auto				&block = at(index);
	auto				texture_index = ivec2(0);

	light_level = max(block_settings::light_level_min, light_level);
	if (axis == axis::x and sign == sign::plus)
	{
		if (block.is_diagonal())
		{
			append_to_vector(workspace.vertices, first_diagonal_vertices);
			append_to_vector(workspace.texture_coordinates, first_diagonal_texture_coordinates);
		}
		else
		{
			append_to_vector(workspace.vertices, right_vertices);
			append_to_vector(workspace.texture_coordinates, right_texture_coordinates);
		}
		texture_index = texture_atlas::get_association(at(index).type).right;
	}
	else if (axis == axis::x and sign == sign::minus)
	{
		if (block.is_diagonal())
		{
			append_to_vector(workspace.vertices, second_diagonal_vertices);
			append_to_vector(workspace.texture_coordinates, second_diagonal_texture_coordinates);
		}
		else
		{
			append_to_vector(workspace.vertices, left_vertices);
			append_to_vector(workspace.texture_coordinates, left_texture_coordinates);
		}
		texture_index = texture_atlas::get_association(at(index).type).left;
	}
	else if (axis == axis::y and sign == sign::plus)
	{
		append_to_vector(workspace.vertices, top_vertices);
		append_to_vector(workspace.texture_coordinates, top_texture_coordinates);
		texture_index = texture_atlas::get_association(at(index).type).top;
	}
	else if (axis == axis::y and sign == sign::minus)
	{
		append_to_vector(workspace.vertices, bottom_vertices);
		append_to_vector(workspace.texture_coordinates, bottom_texture_coordinates);
		texture_index = texture_atlas::get_association(at(index).type).bottom;
	}
	else if (axis == axis::z and sign == sign::plus)
	{
		append_to_vector(workspace.vertices, front_vertices);
		append_to_vector(workspace.texture_coordinates, front_texture_coordinates);
		texture_index = texture_atlas::get_association(at(index).type).front;
	}
	else if (axis == axis::z and sign == sign::minus)
	{
		append_to_vector(workspace.vertices, back_vertices);
		append_to_vector(workspace.texture_coordinates, back_texture_coordinates);
		texture_index = texture_atlas::get_association(at(index).type).back;
	}
	else
		assert(false and "Can't build quad");

	for (int i = (int)workspace.vertices.size() - 12; i < (int)workspace.vertices.size(); i += 3)
	{
		workspace.vertices[i + 0] += (float)index.x;
		workspace.vertices[i + 1] += (float)index.y;
		workspace.vertices[i + 2] += (float)index.z;
	}

	auto				transform_texture_coordinate = [texture_index](float &x, float &y)
	{
		static vec2 	size = texture_atlas::get_texture_size();

		x = size.x *((float)texture_index.x + x);
		y = size.y *((float)texture_index.y + y);
	};

	for (int i = (int)workspace.texture_coordinates.size() - 8; i < (int)workspace.texture_coordinates.size(); i += 2)
		transform_texture_coordinate(workspace.texture_coordinates[i + 0], workspace.texture_coordinates[i + 1]);

	const int			offset = (int)workspace.indices.size() / 6 * 4;

	append_to_vector(workspace.indices, indices);
	for (int i = (int)workspace.indices.size() - 6; i < (int)workspace.indices.size(); i++)
		workspace.indices[i] += offset;

	auto 				normalized_light_level = (float)light_level / block_settings::light_level_max;

	for (int i = 0; i < 4; i++)
		workspace.light_levels.push_back(normalized_light_level);
}