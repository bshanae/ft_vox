#include "chunk.h"

#include "common/aliases.h"
#include "model/model.h"

static vector<float>	vfront =
{
//						those two go to the quad
	0.5f,  0.5f,  0.5f,
	0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,
//						FRONT
	-0.5f,  0.5f,  0.5f
};

static vector<unsigned>	indices =
{
	0,  1,  3,
	1,  2,  3
};

						chunk::chunk() : model(vfront, indices)
						{}

						chunk::chunk(const chunk &other)
{
  //make(other.cstring);
}

chunk					&chunk::operator = (const chunk &other)
{
	if (this != &other)
	{

	}

  	return (*this);
}

void					chunk::render()
{
  model.bind(true);
  //shader
  glDrawElements(GL_TRIANGLES, model.get_number_of_indices(), GL_UNSIGNED_INT, nullptr);
  model.bind(false);
}

model					chunk::get_model()
{
  return (model);
}
