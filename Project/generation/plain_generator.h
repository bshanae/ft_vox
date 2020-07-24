#pragma once
#include "generation/generator.h"

class plain_generator  : public generator {
 public:
  plain_generator()
  {
  }

  float get_noise(float x, float y)
  {
  	return m_noise.GetNoise(x, y);
  }

  float get_noise(float x, float y, float z)
  {
	  return m_noise.GetNoise(x, y, z);
  }
  void print()
  {

  }
};