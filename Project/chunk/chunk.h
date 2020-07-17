#pragma once
#include <memory>
#include "Project/model/model.h"
#include "Project/object/object.h"


class chunk : public object  {

 public:
  chunk();// we got create from object
  ~chunk() = default;
  model get_model();
  void render();

  chunk(const chunk& other); // copy constructor

  chunk& operator=(const chunk& other); // copy assignment

 private:
  model m_model;
};