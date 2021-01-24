#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/string_cast.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/noise.hpp"
#include "glm/gtx/rotate_vector.hpp"

// ---------------- Types

using 				glm::ivec2;
using 				glm::vec2;
using 				glm::ivec3;
using 				glm::vec3;
using 				glm::vec4;
using 				glm::mat3;
using 				glm::mat4;

// ---------------- Matrices

using				glm::perspective;
using				glm::ortho;
using				glm::lookAt;
using				glm::scale;
using				glm::translate;
using				glm::eulerAngleYXZ;
using 				glm::value_ptr;

// ---------------- Vectors

using 				glm::normalize;
using 				glm::distance;
using				glm::length;
using				glm::rotate;

// ---------------- Others

using				glm::fract;
using				glm::mix;
using 				glm::mod;
using				glm::radians;