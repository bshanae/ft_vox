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

						chunk::chunk()
{
	for (auto iterator : *this)
		iterator->get_value().type_value = block::type::dirt;
}

						chunk::chunk(const vec3 &position) : chunk()
{
	this->position = position;
	model::set_translation(vec3(position.x, position.y, position.z));
}

void					chunk::start()
{
	build_model();
}

void					chunk::render()
{
	renderer::render(*this);
}

void					chunk::build_model()
{
	this->vertices.clear();
	this->texture_coordinates.clear();
	this->indices.clear();

	for (auto &iterator : *this)
		build_block(iterator->get_index());

	model = make_shared<::model>(this->vertices, this->texture_coordinates, this->indices);
}

void					chunk::build_block(const index &index)
{
	auto 				this_pointer = dynamic_pointer_cast<chunk>(shared_from_this());
	auto 				try_build_quad = [this, this_pointer, index](axis axis, sign sign)
	{
		auto			neighbor = index.neighbor((::axis)axis, (::sign)sign);

		if (not neighbor)
		{
			auto 		neighbor_chunk = neighbor_provider ? neighbor_provider(this_pointer, axis, sign) : nullptr;
			auto		reflected = neighbor.reflect();

			if (neighbor_chunk and not neighbor_chunk->at(reflected).empty())
				;
			else
				build_quad((::axis)axis, (::sign)sign, index);
		}
		else if (at(neighbor).empty())
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
	if (axis == axis::x and sign == sign::plus)
	{
		append_to_vector(vertices, right_vertices);
		append_to_vector(texture_coordinates, right_texture_coordinates);
	}
	else if (axis == axis::x and sign == sign::minus)
	{
		append_to_vector(vertices, left_vertices);
		append_to_vector(texture_coordinates, left_texture_coordinates);
	}
	else if (axis == axis::y and sign == sign::plus)
	{
		append_to_vector(vertices, top_vertices);
		append_to_vector(texture_coordinates, top_texture_coordinates);
	}
	else if (axis == axis::y and sign == sign::minus)
	{
		append_to_vector(vertices, bottom_vertices);
		append_to_vector(texture_coordinates, bottom_texture_coordinates);
	}
	else if (axis == axis::z and sign == sign::plus)
	{
		append_to_vector(vertices, front_vertices);
		append_to_vector(texture_coordinates, front_texture_coordinates);
	}
	else if (axis == axis::z and sign == sign::minus)
	{
		append_to_vector(vertices, back_vertices);
		append_to_vector(texture_coordinates, back_texture_coordinates);
	}
	else
		assert(false and "Can't build quad");

	for (int i = (int)vertices.size() - 12; i < (int)vertices.size(); i += 3)
	{
		vertices[i + 0] += (float)index.x;
		vertices[i + 1] += (float)index.y;
		vertices[i + 2] += (float)index.z;
	}

	auto				transform_texture_coordinate = [](float &x, float &y)
	{
		vec2 			size = texture_atlas::get_texture_size();
		vec2			position = texture_atlas::get_texture_position(block::type::dirt);

		x = position.x + size.x * x;
		y = position.y + size.y * y;
	};

	for (int i = (int)texture_coordinates.size() - 8; i < (int)texture_coordinates.size(); i += 2)
		transform_texture_coordinate(texture_coordinates[i + 0], texture_coordinates[i + 1]);

	const int			offset = (int)this->indices.size() / 6 * 4;

	append_to_vector(indices, ::indices);
	for (int i = (int)this->indices.size() - 6; i < (int)this->indices.size(); i++)
		this->indices[i] += offset;
}