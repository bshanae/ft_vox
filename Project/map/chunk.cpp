#include "chunk.h"

#include "common/aliases.h"
#include "map/model.h"
#include "renderer/renderer.h"
#include "map/texture_atlas.h"
#include "map/map.h"

static vector<GLfloat>	front_vertices = {
	+0.5f, +0.5f, +0.5f,
	-0.5f, +0.5f, +0.5f,
	-0.5f, -0.5f, +0.5f,
	+0.5f, -0.5f, +0.5f
};

static vector<GLfloat>	front_texture_coordinates = {
	1.f, 1.f,
	0.f, 1.f,
	0.f, 0.f,
	1.f, 0.f,
};

static vector<GLfloat>	back_vertices = {
	+0.5f, +0.5f, -0.5f,
	+0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, +0.5f, -0.5f
};

static vector<GLfloat>	back_texture_coordinates = {
	0.f, 1.f,
	0.f, 0.f,
	1.f, 0.f,
	1.f, 1.f,
};

static vector<GLfloat>	top_vertices = {
	-0.5f, +0.5f, +0.5f,
	+0.5f, +0.5f, +0.5f,
	+0.5f, +0.5f, -0.5f,
	-0.5f, +0.5f, -0.5f
};

static vector<GLfloat>	top_texture_coordinates = {
	0.f, 0.f,
	1.f, 0.f,
	1.f, 1.f,
	0.f, 1.f,
};

static vector<GLfloat>	bottom_vertices = {
	-0.5f, -0.5f, +0.5f,
	-0.5f, -0.5f, -0.5f,
	+0.5f, -0.5f, -0.5f,
	+0.5f, -0.5f, +0.5f
};

static vector<GLfloat>	bottom_texture_coordinates = {
	0.f, 0.f,
	0.f, 1.f,
	1.f, 1.f,
	1.f, 0.f,
};

static vector<GLfloat>	right_vertices = {
	+0.5f, +0.5f, +0.5f,
	+0.5f, -0.5f, +0.5f,
	+0.5f, -0.5f, -0.5f,
	+0.5f, +0.5f, -0.5f
};

static vector<GLfloat>	right_texture_coordinates = {
	0.f, 1.f,
	0.f, 0.f,
	1.f, 0.f,
	1.f, 1.f,
};

static vector<GLfloat>	left_vertices = {
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, +0.5f,
	-0.5f, +0.5f, +0.5f,
	-0.5f, +0.5f, -0.5f,
};

static vector<GLfloat>	left_texture_coordinates = {
	0.f, 0.f,
	1.f, 0.f,
	1.f, 1.f,
	0.f, 1.f
};


static vector<GLuint>	indices =
{
	0, 1, 3,
	1, 2, 3
};

						chunk::chunk(const vec3 &position)
{
	this->position = position;
	this->center.getter = [this](){ return (*this->position + chunk_settings::size_as_vector / 2.f); };

//	for (auto iterator : *this)
//		iterator.value().type_value = block::type::dirt;

	index i;
	i.y = chunk_settings::size[1] - 4;
	for (i.x = 0; i.x < chunk_settings::size[0]; i.x++)
		for (i.z = 0; i.z < chunk_settings::size[2]; i.z++)
			at(i).type = block::type::dirt;

	at(0, chunk_settings::size[1] - 2 , 0).type = block::type::dirt_with_grass;
}

						pair<shared_ptr<chunk>, chunk::index>
						chunk::neighbor_block_from_another_chunk(const index &index, axis axis, sign sign)
{
	chunk::index		neighbor_index;
	chunk::index		reflected_index;
	shared_ptr<chunk>	neighbor_chunk;

	neighbor_chunk = map::neighbor_chunk(dynamic_pointer_cast<chunk>(shared_from_this()), axis, sign);
	if (neighbor_chunk == nullptr)
		return {nullptr, chunk::index(-1, -1, -1)};

	neighbor_index = index.neighbor(axis, sign);
	reflected_index = neighbor_index.reflect();

	return {neighbor_chunk, reflected_index};
}

void					chunk::render()
{
	renderer::render(*this);
}

void					chunk::build_model()
{
	this->vertices.clear();
	this->texture_coordinates.clear();
	this->light_levels.clear();
	this->indices.clear();

	for (auto &iterator : *this)
		build_block(iterator.index());

	model = make_shared<::model>();

	model->translation = *position;
	model->bind(true);

	model->add_vbo(3, this->vertices);
	model->add_vbo(2, this->texture_coordinates);
	model->add_vbo(1, this->light_levels);
	model->add_ebo(this->indices);

	model->bind(false);
}

void					chunk::build(build_request request)
{
	switch (request)
	{
		case (build_request::reset) :
			build_phase = build_phase::nothing_done;
			model = nullptr;
			break ;

		case (build_request::light) :
			assert(build_phase == build_phase::nothing_done and "Unexpected build phase");
			calculate_light();
			build_phase = build_phase::light_done;
			break ;

		case (build_request::model) :
			assert(build_phase == build_phase::light_done and "Unexpected build phase");
			build_model();
			build_phase = build_phase::model_done;
			break ;
	}
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

void					chunk::build_block(const index &index)
{
	auto 				try_build_quad = [this, index](axis axis, sign sign)
	{
		auto			neighbor_index = index.neighbor((::axis)axis, (::sign)sign);

		if (not neighbor_index)
		{
			auto		neighbor_data = neighbor_block_from_another_chunk(index, axis, sign);

			if (neighbor_data.first == nullptr)
				build_quad(index, (::axis)axis, (::sign)sign, block_settings::default_light_level);
			else if (auto neighbor_block = neighbor_data.first->at(neighbor_data.second); neighbor_block.is_empty())
				build_quad(index, (::axis)axis, (::sign)sign, neighbor_block.light_level);
		}
		else if (auto neighbor_block = at(neighbor_index); neighbor_block.is_empty())
			build_quad(index, (::axis)axis, (::sign)sign, neighbor_block.light_level);
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
	ivec2 				texture_index = ivec2(0);

	light_level = max(block_settings::light_level_min, light_level);
	if (axis == axis::x and sign == sign::plus)
	{
		append_to_vector(vertices, right_vertices);
		append_to_vector(texture_coordinates, right_texture_coordinates);
		texture_index = texture_atlas::association_for(at(index).type).right;
	}
	else if (axis == axis::x and sign == sign::minus)
	{
		append_to_vector(vertices, left_vertices);
		append_to_vector(texture_coordinates, left_texture_coordinates);
		texture_index = texture_atlas::association_for(at(index).type).left;
	}
	else if (axis == axis::y and sign == sign::plus)
	{
		append_to_vector(vertices, top_vertices);
		append_to_vector(texture_coordinates, top_texture_coordinates);
		texture_index = texture_atlas::association_for(at(index).type).top;
	}
	else if (axis == axis::y and sign == sign::minus)
	{
		append_to_vector(vertices, bottom_vertices);
		append_to_vector(texture_coordinates, bottom_texture_coordinates);
		texture_index = texture_atlas::association_for(at(index).type).bottom;
	}
	else if (axis == axis::z and sign == sign::plus)
	{
		append_to_vector(vertices, front_vertices);
		append_to_vector(texture_coordinates, front_texture_coordinates);
		texture_index = texture_atlas::association_for(at(index).type).front;
	}
	else if (axis == axis::z and sign == sign::minus)
	{
		append_to_vector(vertices, back_vertices);
		append_to_vector(texture_coordinates, back_texture_coordinates);
		texture_index = texture_atlas::association_for(at(index).type).back;
	}
	else
		assert(false and "Can't build quad");

	for (int i = (int)vertices.size() - 12; i < (int)vertices.size(); i += 3)
	{
		vertices[i + 0] += (float)index.x;
		vertices[i + 1] += (float)index.y;
		vertices[i + 2] += (float)index.z;
	}

	auto				transform_texture_coordinate = [this, texture_index](float &x, float &y)
	{
		static vec2 	size = texture_atlas::texture_size();

		x = size.x *((float)texture_index.x + x);
		y = size.y *((float)texture_index.y + y);
	};

	for (int i = (int)texture_coordinates.size() - 8; i < (int)texture_coordinates.size(); i += 2)
		transform_texture_coordinate(texture_coordinates[i + 0], texture_coordinates[i + 1]);

	const int			offset = (int)this->indices.size() / 6 * 4;

	append_to_vector(indices, ::indices);
	for (int i = (int)this->indices.size() - 6; i < (int)this->indices.size(); i++)
		this->indices[i] += offset;

	auto 				normalized_light_level = (float)light_level / block_settings::light_level_max;

	for (int i = 0; i < 4; i++)
		light_levels.push_back(normalized_light_level);
}