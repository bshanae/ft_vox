#include "chunk.h"

#include "common/aliases.h"
#include "world/block/block_settings.h"
#include "world/block/texture_atlas.h"
#include "world/chunk/model.h"

static const float		epsilon = 0.005f;

static vector<GLfloat>	front_vertices = {
	+0.5f, +0.5f, +0.5f,
	-0.5f, +0.5f, +0.5f,
	-0.5f, -0.5f, +0.5f,
	+0.5f, -0.5f, +0.5f
};

static vector<GLfloat>	front_texture_coordinates = {
	1.f - epsilon, 1.f - epsilon,
	0.f + epsilon, 1.f - epsilon,
	0.f + epsilon, 0.f + epsilon,
	1.f - epsilon, 0.f + epsilon,
};

static vector<GLfloat>	back_vertices = {
	+0.5f, +0.5f, -0.5f,
	+0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, +0.5f, -0.5f
};

static vector<GLfloat>	back_texture_coordinates = {
	0.f + epsilon, 1.f - epsilon,
	0.f + epsilon, 0.f + epsilon,
	1.f - epsilon, 0.f + epsilon,
	1.f - epsilon, 1.f - epsilon,
};

static vector<GLfloat>	top_vertices = {
	-0.5f, +0.5f, +0.5f,
	+0.5f, +0.5f, +0.5f,
	+0.5f, +0.5f, -0.5f,
	-0.5f, +0.5f, -0.5f
};

static vector<GLfloat>	top_texture_coordinates = {
	0.f + epsilon, 0.f + epsilon,
	1.f - epsilon, 0.f + epsilon,
	1.f - epsilon, 1.f - epsilon,
	0.f + epsilon, 1.f - epsilon,
};

static vector<GLfloat>	bottom_vertices = {
	-0.5f, -0.5f, +0.5f,
	-0.5f, -0.5f, -0.5f,
	+0.5f, -0.5f, -0.5f,
	+0.5f, -0.5f, +0.5f
};

static vector<GLfloat>	bottom_texture_coordinates = {
	0.f + epsilon, 0.f + epsilon,
	0.f + epsilon, 1.f - epsilon,
	1.f - epsilon, 1.f - epsilon,
	1.f - epsilon, 0.f + epsilon,
};

static vector<GLfloat>	right_vertices = {
	+0.5f, +0.5f, +0.5f,
	+0.5f, -0.5f, +0.5f,
	+0.5f, -0.5f, -0.5f,
	+0.5f, +0.5f, -0.5f
};

static vector<GLfloat>	right_texture_coordinates = {
	0.f + epsilon, 1.f - epsilon,
	0.f + epsilon, 0.f + epsilon,
	1.f - epsilon, 0.f + epsilon,
	1.f - epsilon, 1.f - epsilon,
};

static vector<GLfloat>	left_vertices = {
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, +0.5f,
	-0.5f, +0.5f, +0.5f,
	-0.5f, +0.5f, -0.5f,
};

static vector<GLfloat>	left_texture_coordinates = {
	0.f + epsilon, 0.f + epsilon,
	1.f - epsilon, 0.f + epsilon,
	1.f - epsilon, 1.f - epsilon,
	0.f + epsilon, 1.f - epsilon
};


static vector<GLuint>	indices =
{
	0, 1, 3,
	1, 2, 3
};

						chunk::chunk(const vec3 &position)
{
	this->position = position;
	center.getter = [this](){ return (*this->position + chunk_settings::size_as_vector / 2.f); };
	center.prohibit_direct_access();

	main_workspace = make_shared<model_workspace>();
	main_workspace->predicate = [](enum block::type type){ return (type != block::type::water); };

	water_workspace = make_shared<model_workspace>();
	water_workspace->predicate = [](enum block::type type){ return (type == block::type::water); };

	index i;
	i.y = chunk_settings::size[1] - 1;
	for (i.x = 0; i.x < chunk_settings::size[0]; i.x++)
		for (i.z = 0; i.z < chunk_settings::size[2]; i.z++)
			at(i).type = block::type::dirt;
	i.y = chunk_settings::size[1] - 2;
	for (i.x = 0; i.x < chunk_settings::size[0]; i.x++)
		for (i.z = 0; i.z < chunk_settings::size[2]; i.z++)
			at(i).type = block::type::dirt;

	at(1, chunk_settings::size[1] - 1 , 0).type = block::type::water;
	at(2, chunk_settings::size[1] - 1 , 0).type = block::type::water;
}

void					chunk::build(build_request request)
{
	switch (request)
	{
		case (build_request::reset) :
			build_phase = build_phase::nothing_done;

			main_workspace->vertices.clear();
			main_workspace->texture_coordinates.clear();
			main_workspace->light_levels.clear();
			main_workspace->indices.clear();
			main_workspace->model.reset();

			water_workspace->vertices.clear();
			water_workspace->texture_coordinates.clear();
			water_workspace->light_levels.clear();
			water_workspace->indices.clear();
			water_workspace->model.reset();

			break ;

		case (build_request::light) :
			assert(build_phase == build_phase::nothing_done and "Unexpected build phase");
			calculate_light();
			build_phase = build_phase::light_done;
			break ;

		case (build_request::model) :
			assert(build_phase == build_phase::light_done and "Unexpected build phase");
			workspace = main_workspace;
			build_model();
			workspace = water_workspace;
			build_model();
			build_phase = build_phase::model_done;
			break ;
	}
}

void					chunk::show()
{
//	if (main_workspace and main_workspace->model)
//		main_workspace->model->activate();
//	if (water_workspace and water_workspace->model)
//		water_workspace->model->activate();
}

void					chunk::hide()
{
//	if (main_workspace and main_workspace->model)
//		main_workspace->model->deactivate();
//	if (water_workspace and water_workspace->model)
//		water_workspace->model->deactivate();
}

void					chunk::calculate_light()
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

		if (neighbor_index = index.neighbor(axis::y, sign::minus); not neighbor_index)
			continue ;
		if (not at(neighbor_index).is_empty())
			continue ;
		if (at(index).light_level - at(neighbor_index).light_level >= 2)
		{
			at(neighbor_index).light_level = (char)(at(index).light_level);
			queue.push(neighbor_index);
		}
	}
}

float					chunk::calculate_ao(const index &index, axis axis, sign sign)
{
	optional<block_id>	central_neighbor;

	central_neighbor = block_id(shared_from_this(), index).neighbor(axis, sign);
	if (not central_neighbor)
		return (0.f);

	int					occluders_count = 0;
	const int 			occluders_max_count = 8 * 2;

	optional<block_id>	occluder;
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
						occluder = occluder->neighbor((::axis)first_axis, (::sign)first_sign);
					if (second_sign != 0 and occluder)
						occluder = occluder->neighbor((::axis)second_axis, (::sign)second_sign);

					if (occluder and not (*occluder)().is_empty())
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
	const char			dynamic_part = (float)light_level * 0.8f;
	const char			static_part = light_level - dynamic_part;

	const char			ao_result = (float)dynamic_part * (1.f - ao);

	return (static_part + ao_result);
}

void					chunk::build_model()
{
	workspace->vertices.clear();
	workspace->texture_coordinates.clear();
	workspace->light_levels.clear();
	workspace->indices.clear();

	for (auto &iterator : *this)
		if (workspace->predicate(iterator->value().type))
			build_block(iterator.index());

	workspace->model = make_shared<model>();

//	vec3(0.5f) is block offset, so first block is on vec3(0, 0, 0)
	workspace->model->translation = (vec3)position + vec3(0.5f);
	workspace->model->bind(true);

	workspace->model->add_vbo(3, workspace->vertices);
	workspace->model->add_vbo(2, workspace->texture_coordinates);
	workspace->model->add_vbo(1, workspace->light_levels);
	workspace->model->add_ebo(workspace->indices);

	workspace->model->bind(false);
}

void					chunk::build_block(const index &index)
{
	auto 				try_build_quad = [this, index](axis axis, sign sign)
	{
		auto			this_block_id = block_id(shared_from_this(), index);
		auto 			neighbor_block_id = this_block_id.neighbor(axis, sign);

		if (neighbor_block_id)
		{
			auto 		this_block = this_block_id();
			auto 		neighbor_block = (*neighbor_block_id)();

			if (not this_block.is_transparent() and neighbor_block.is_transparent());
			else if (neighbor_block.is_empty());
			else
				return ;

			auto		ao = calculate_ao(index, axis, sign);
			auto		light_level = apply_ao(neighbor_block.light_level, ao);

			build_quad(index, (::axis)axis, (::sign)sign, light_level);
		}
		else if (not neighbor_block_id)
			build_quad(index, (::axis)axis, (::sign)sign, block_settings::default_light_level);
	};

	if (at(index).is_empty())
		return ;

	for (int axis = (int)axis::x; axis <= (int)axis::z; axis++)
	{
		try_build_quad((::axis)axis, sign::minus);
		try_build_quad((::axis)axis, sign::plus);
	}
}

template				<typename type>
void					append_to_vector(vector<type> &target, const vector<type> &source)
{
	target.insert(target.end(), source.begin(), source.end());
}

void					chunk::build_quad(const index &index, axis axis, sign sign, char light_level)
{
	auto				texture_index = ivec2(0);

	light_level = max(block_settings::light_level_min, light_level);
	if (axis == axis::x and sign == sign::plus)
	{
		append_to_vector(workspace->vertices, right_vertices);
		append_to_vector(workspace->texture_coordinates, right_texture_coordinates);
		texture_index = texture_atlas::association_for(at(index).type).right;
	}
	else if (axis == axis::x and sign == sign::minus)
	{
		append_to_vector(workspace->vertices, left_vertices);
		append_to_vector(workspace->texture_coordinates, left_texture_coordinates);
		texture_index = texture_atlas::association_for(at(index).type).left;
	}
	else if (axis == axis::y and sign == sign::plus)
	{
		append_to_vector(workspace->vertices, top_vertices);
		append_to_vector(workspace->texture_coordinates, top_texture_coordinates);
		texture_index = texture_atlas::association_for(at(index).type).top;
	}
	else if (axis == axis::y and sign == sign::minus)
	{
		append_to_vector(workspace->vertices, bottom_vertices);
		append_to_vector(workspace->texture_coordinates, bottom_texture_coordinates);
		texture_index = texture_atlas::association_for(at(index).type).bottom;
	}
	else if (axis == axis::z and sign == sign::plus)
	{
		append_to_vector(workspace->vertices, front_vertices);
		append_to_vector(workspace->texture_coordinates, front_texture_coordinates);
		texture_index = texture_atlas::association_for(at(index).type).front;
	}
	else if (axis == axis::z and sign == sign::minus)
	{
		append_to_vector(workspace->vertices, back_vertices);
		append_to_vector(workspace->texture_coordinates, back_texture_coordinates);
		texture_index = texture_atlas::association_for(at(index).type).back;
	}
	else
		assert(false and "Can't build quad");

	for (int i = (int)workspace->vertices.size() - 12; i < (int)workspace->vertices.size(); i += 3)
	{
		workspace->vertices[i + 0] += (float)index.x;
		workspace->vertices[i + 1] += (float)index.y;
		workspace->vertices[i + 2] += (float)index.z;
	}

	auto				transform_texture_coordinate = [this, texture_index](float &x, float &y)
	{
		static vec2 	size = texture_atlas::texture_size();

		x = size.x *((float)texture_index.x + x);
		y = size.y *((float)texture_index.y + y);
	};

	for (int i = (int)workspace->texture_coordinates.size() - 8; i < (int)workspace->texture_coordinates.size(); i += 2)
		transform_texture_coordinate(workspace->texture_coordinates[i + 0], workspace->texture_coordinates[i + 1]);

	const int			offset = (int)workspace->indices.size() / 6 * 4;

	append_to_vector(workspace->indices, indices);
	for (int i = (int)workspace->indices.size() - 6; i < (int)workspace->indices.size(); i++)
		workspace->indices[i] += offset;

	auto 				normalized_light_level = (float)light_level / block_settings::light_level_max;

	for (int i = 0; i < 4; i++)
		workspace->light_levels.push_back(normalized_light_level);
}