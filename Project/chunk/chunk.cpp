#include "chunk.h"

#include "common/aliases.h"
#include "model.h"

static float			front[] ={
	+0.5f, +0.5f, +0.5f,
	+0.5f, -0.5f, +0.5f,
	-0.5f, -0.5f, +0.5f,
	-0.5f, +0.5f, +0.5f
};

static float			back[] = {
	+0.5f, +0.5f, -0.5f,
	+0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, +0.5f, -0.5f
};

static float			top[] = {
	-0.5f, +0.5f, +0.5f,
	-0.5f, +0.5f, -0.5f,
	+0.5f, +0.5f, -0.5f,
	+0.5f, +0.5f, +0.5f
};

static float			bottom[] = {
	-0.5f, -0.5f, +0.5f,
	-0.5f, -0.5f, -0.5f,
	+0.5f, -0.5f, -0.5f,
	+0.5f, -0.5f, +0.5f
};

static float			right[] = {
	+0.5f, +0.5f, +0.5f,
	+0.5f, -0.5f, +0.5f,
	+0.5f, -0.5f, -0.5f,
	+0.5f, +0.5f, -0.5f
};

static float			left[] = {
	-0.5f, -0.5f, -0.5f,
	-0.5f, +0.5f, -0.5f,
	-0.5f, +0.5f, +0.5f,
	-0.5f, -0.5f, +0.5f
};

static GLuint			indices[] =
{
	0, 1, 3,
	1, 2, 3
};

						chunk::chunk()
{
	this->vertices.insert(vertices.end(), front, front + 12);
	this->indices.insert(indices.end(), ::indices, ::indices + 6);
	model = make_shared<::model>(this->vertices, this->indices);
}

void					chunk::render()
{
	if (not renderer)
		renderer = make_unique<class renderer>();

	renderer->render(*this);
}

void					chunk::build_block(block block_type, ivec3 index)
{
	ivec3					neighbor;

	for (int i = (int)direction::begin + 1; i < (int)direction::end; i++)
	{
		if (neighbor = get_neighbor(index, (direction)i); does_index_exist(neighbor) and not is_block_empty(neighbor))
			build_quad((direction)i, index);
	}
}

void					chunk::build_quad(direction direction, ivec3 index)
{
	switch (direction)
	{
		case (direction::left) :
			vertices.insert(vertices.end(), left, left + 12);
			break ;

		case (direction::right) :
			vertices.insert(vertices.end(), right, right + 12);
			break ;

		case (direction::bottom) :
			vertices.insert(vertices.end(), bottom, bottom + 12);
			break ;

		case (direction::top) :
			vertices.insert(vertices.end(), top, top + 12);
			break ;

		case (direction::back) :
			vertices.insert(vertices.end(), back, back + 12);
			break ;

		case (direction::front) :
			vertices.insert(vertices.end(), front, front + 12);
			break ;

		default :
			assert(false and "Unexpected switch branch");
	}

	for (int i = vertices.size() - 12; i < (int)vertices.size(); i += 3)
	{
		vertices[i + 0] += index.x;
		vertices[i + 1] += index.y;
		vertices[i + 2] += index.z;
	}

	const int			old_size = this->indices.size();

	this->indices.insert(indices.end(), ::indices, ::indices + 6);
	for (int i = this->indices.size() - 12; i < (int)this->indices.size(); i++)
		this->indices[i] += old_size;
}