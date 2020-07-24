#include "chunk.h"

#include "common/aliases.h"
#include "chunk/model.h"
#include "chunk/renderer.h"

static float			front[] = {
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
	build_model();
}

void					chunk::render()
{
	renderer::render(*this);
}

void					chunk::build_model()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			blocks[i][0][j].type = block::type::dirt;

	this->vertices.clear();
	this->indices.clear();

	for (int iter_x = 0; iter_x < blocks.size(); iter_x++)
		for (int iter_y = 0; iter_y < blocks[iter_x].size(); iter_y++)
			for (int iter_z = 0; iter_z < blocks[iter_x][iter_z].size(); iter_z++)
				build_block(ivec3(iter_x, iter_y, iter_z));

	model = make_shared<::model>(this->vertices, this->indices);
}

void					chunk::build_block(ivec3 index)
{
	ivec3				neighbor;
	bool 				does_neighbor_exist;

	if (is_block_empty(index))
		return ;
	for (int i = (int)direction::begin + 1; i < (int)direction::end; i++)
	{
		neighbor = get_neighbor_block(index, (direction)i);
		does_neighbor_exist = does_block_exist(neighbor);

		if ((does_neighbor_exist and is_block_empty(neighbor)) or not does_neighbor_exist)
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

	const int			offset = this->indices.size() / 6 * 4;

	this->indices.insert(indices.end(), ::indices, ::indices + 6);
	for (int i = this->indices.size() - 6; i < (int)this->indices.size(); i++)
		this->indices[i] += offset;
}

ivec3					chunk::get_neighbor_block(ivec3 index, direction direction)
{
	switch (direction)
	{
		case (direction::left) :
			return (index + ivec3(-1, 0, 0));

		case (direction::right) :
			return (index + ivec3(1, 0, 0));

		case (direction::bottom) :
			return (index + ivec3(0, -1, 0));

		case (direction::top) :
			return (index + ivec3(0, 1, 0));

		case (direction::back) :
			return (index + ivec3(0, 0, -1));

		case (direction::front) :
			return (index + ivec3(0, 0, 1));

		default :
			return (index);
	}
}

bool					chunk::does_block_exist(ivec3 index)
{
	if (index.x < 0 or index.x >= size[0])
		return (false);
	if (index.y < 0 or index.y >= size[1])
		return (false);
	if (index.z < 0 or index.z >= size[2])
		return (false);
	return (true);
}

bool					chunk::is_block_empty(ivec3 index)
{
	return (blocks[index.x][index.y][index.z].is_empty());
}