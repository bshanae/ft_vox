#pragma once

#include "model/model.h"
#include "object/object.h"

class				chunk : public object
{
public :
#warning "We got create from object"
					chunk();
  					~chunk() = default;

  model				get_model();
  void				render() override;

  					chunk(const chunk& other);
  chunk				&operator = (const chunk& other);

private :

	model			model;
};