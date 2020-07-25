#pragma once
#include "common/global.h"
#include "generation/generator.h"
#include "generation/plain_generator.h"
#include <vector>

class generator_controller : public global <generator_controller>  {

  friend class			application;

 public:
  enum class generator_type
  {
	plain = 0
  };
  static void		execute()
  {
	  auto		instance = global<generator_controller>::instance();
	  //instance->m_generators->push_back(plain_generator());
	  instance->m_generators.push_back(std::make_shared<plain_generator>());
  }
  std::shared_ptr<generator> get_generator(generator_type type)
  {
	return instance()->m_generators[static_cast<unsigned long>(type)];
  }
 private:
  	std::vector<std::shared_ptr<generator>> m_generators;
};

