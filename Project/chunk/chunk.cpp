//
// Created by Oles Gedz on 17/07/2020.
//

#include "chunk.h"
#include "Project/model/model.h"
#include <vector>
static std::vector<float> vfront ={		//those two go to the quad
	0.5f,  0.5f,  0.5f,
	0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,   //FRONT
	-0.5f,  0.5f,  0.5f
};
static std::vector<unsigned int> indices = {
	0,  1,  3,
	1,  2,  3
};
chunk::chunk() :
	m_model(vfront, indices)
{


}
chunk::chunk(const chunk& other) // copy constructor
{
  //make(other.cstring);
}

chunk& chunk::operator=(const chunk& other) // copy assignment
{
  if(this != &other) {
//	this.model.de
  }
  return *this;
}

void chunk::render()
{
  m_model.bind();
  //shader

  glDrawElements(GL_TRIANGLES, m_model.getIndicesCount(), GL_UNSIGNED_INT, nullptr);
  m_model.unbind();
}
model chunk::get_model() {
  return m_model;
}
