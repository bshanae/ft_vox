#include "chunk.h"

#include "common/aliases.h"
#include "map/model.h"
#include "map/renderer.h"

static float			front[] = {
	+0.5f, +0.5f, +0.5f,
	-0.5f, +0.5f, +0.5f,
	-0.5f, -0.5f, +0.5f,
	+0.5f, -0.5f, +0.5f
};

static float			back[] = {
	+0.5f, +0.5f, -0.5f,
	+0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, +0.5f, -0.5f
};

static float			top[] = {
	-0.5f, +0.5f, +0.5f,
	+0.5f, +0.5f, +0.5f,
	+0.5f, +0.5f, -0.5f,
	-0.5f, +0.5f, -0.5f
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
	-0.5f, -0.5f, +0.5f,
	-0.5f, +0.5f, +0.5f,
	-0.5f, +0.5f, -0.5f,
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
	blocks_type::index	index;

	for (index.x = 0; index.x < 4; index.x++)
		for (index.z = 0; index.z < 4; index.z++)
			blocks.at(index).type = block::type::dirt;

	this->vertices.clear();
	this->indices.clear();

	for (auto &iterator : blocks)
		build_block(iterator->get_index());

	model = make_shared<::model>(this->vertices, this->indices);
}

void					chunk::build_block(const blocks_type::index &index)
{
	auto 				try_build_quad = [this](axis axis, sign sign, const blocks_type::index &index)
	{
		auto			neighbor = index.neighbor((::axis)axis, (::sign)sign);

		if (not neighbor)
			build_quad((::axis)axis, (::sign)sign, index);
		else if (blocks.at(neighbor).empty())
			build_quad((::axis)axis, (::sign)sign, index);
	};

	if (blocks.at(index).empty())
		return ;
	for (int axis = (int)axis::x; axis <= (int)axis::z; axis++)
	{
		try_build_quad((::axis)axis, sign::minus, index);
		try_build_quad((::axis)axis, sign::plus, index);
	}
}

void					chunk::build_quad(axis axis, sign sign, const blocks_type::index &index)
{
	if (axis == axis::x and sign == sign::plus)
		vertices.insert(vertices.end(), right, right + 12);
	else if (axis == axis::x and sign == sign::minus)
		vertices.insert(vertices.end(), left, left + 12);
	else if (axis == axis::y and sign == sign::plus)
		vertices.insert(vertices.end(), top, top + 12);
	else if (axis == axis::y and sign == sign::minus)
		vertices.insert(vertices.end(), bottom, bottom + 12);
	else if (axis == axis::z and sign == sign::plus)
		vertices.insert(vertices.end(), front, front + 12);
	else if (axis == axis::z and sign == sign::minus)
		vertices.insert(vertices.end(), back, back + 12);
	else
		assert(false and "Can't build quad");

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