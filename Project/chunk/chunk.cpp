#include "chunk.h"

#include "common/aliases.h"
#include "model/model.h"

static vector<float>	vertices =
{
	0.5f, 0.5f, 0.5f,
	0.5f, -0.5f, 0.5f,
	-0.5f, -0.5f, 0.5f,
	-0.5f, 0.5f, 0.5f
};

static vector<GLuint>	indices =
{
	0,  1,  3,
	1,  2,  3
};

						chunk::chunk() : model(vertices, indices)
{}

						chunk::chunk(const chunk &other)
{}

chunk					&chunk::operator = (const chunk &other)
{
	if (this != &other);
	return (*this);
}

void					chunk::render()
{
	if (not renderer)
		renderer = make_unique<class renderer>();

	renderer->render(*this);
}