#include "chunk.h"

#include "common/aliases.h"
#include "map/model.h"
#include "renderer/renderer.h"
#include "map/texture_atlas.h"

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
	model::set_translation(position);

	for (auto iterator : *this)
		iterator.value().type_value = block::type::dirt;
}

void					chunk::render()
{
	renderer::render(*this);
}

void					chunk::build_model()
{
	assert(not is_built and "Should rebuild chunk model");

	this->vertices.clear();
	this->texture_coordinates.clear();
	this->indices.clear();

	for (auto &iterator : *this)
		build_block(iterator.index());

	model = make_shared<::model>(this->vertices, this->texture_coordinates, this->indices);
	is_built = true;
}

void					chunk::build_block(const index &index)
{
	auto 				this_pointer = dynamic_pointer_cast<chunk>(shared_from_this());
	auto 				try_build_quad = [this, this_pointer, index](axis axis, sign sign)
	{
		auto			neighbor_index = index.neighbor((::axis)axis, (::sign)sign);

		if (not neighbor_index)
		{
			assert(neighbor_provider != nullptr and "Neighbor provider is null");

			auto 		neighbor_chunk = neighbor_provider(this_pointer, axis, sign);
			auto		reflected = neighbor_index.reflect();

			if (neighbor_chunk and not neighbor_chunk->at(reflected).empty())
				;
			else
				build_quad((::axis)axis, (::sign)sign, index);
		}
		else if (at(neighbor_index).empty())
			build_quad((::axis)axis, (::sign)sign, index);
	};

	if (at(index).empty())
		return ;

	for (int axis = (int)axis::x; axis <= (int)axis::z; axis++)
	{
		try_build_quad((::axis)axis, sign::minus);
		try_build_quad((::axis)axis, sign::plus);
	}
}

void					chunk::build_quad(axis axis, sign sign, const index &index)
{
	ivec2 				texture_index = ivec2(0);

	if (axis == axis::x and sign == sign::plus)
	{
		append_to_vector(vertices, right_vertices);
		append_to_vector(texture_coordinates, right_texture_coordinates);
		texture_index = texture_atlas::association_for(at(index).type_value).right;
	}
	else if (axis == axis::x and sign == sign::minus)
	{
		append_to_vector(vertices, left_vertices);
		append_to_vector(texture_coordinates, left_texture_coordinates);
		texture_index = texture_atlas::association_for(at(index).type_value).left;
	}
	else if (axis == axis::y and sign == sign::plus)
	{
		append_to_vector(vertices, top_vertices);
		append_to_vector(texture_coordinates, top_texture_coordinates);
		texture_index = texture_atlas::association_for(at(index).type_value).top;
	}
	else if (axis == axis::y and sign == sign::minus)
	{
		append_to_vector(vertices, bottom_vertices);
		append_to_vector(texture_coordinates, bottom_texture_coordinates);
		texture_index = texture_atlas::association_for(at(index).type_value).bottom;
	}
	else if (axis == axis::z and sign == sign::plus)
	{
		append_to_vector(vertices, front_vertices);
		append_to_vector(texture_coordinates, front_texture_coordinates);
		texture_index = texture_atlas::association_for(at(index).type_value).front;
	}
	else if (axis == axis::z and sign == sign::minus)
	{
		append_to_vector(vertices, back_vertices);
		append_to_vector(texture_coordinates, back_texture_coordinates);
		texture_index = texture_atlas::association_for(at(index).type_value).back;
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
}