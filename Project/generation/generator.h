#pragma once
#include "libraries/FastNoise/FastNoise.h"
#include <iostream>
#include <array>
#include <algorithm>
#include <cmath>
class generator {
 public:
  FastNoise m_noise;
  generator() = default;
  ~generator() = default;
  virtual  float get_noise(float x, float y) = 0;
  virtual  float get_noise(float x, float y, float z) = 0;

 private:
};

