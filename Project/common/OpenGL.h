#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "libraries/glm/glm/glm.hpp"
#include "libraries/glm/glm/gtc/quaternion.hpp"
#include "libraries/glm/glm/gtc/matrix_transform.hpp"
#include "libraries/glm/glm/gtc/type_ptr.hpp"
#include "libraries/glm/glm/gtx/string_cast.hpp"
#include "libraries/glm/glm/gtx/euler_angles.hpp"
#include "libraries/glm/glm/gtx/transform.hpp"

using 				glm::ivec2;
using 				glm::vec2;
using 				glm::ivec3;
using 				glm::vec3;
using 				glm::vec4;
using 				glm::mat4;

using				glm::perspective;
using				glm::lookAt;
using				glm::scale;
using				glm::translate;
using				glm::eulerAngleYXZ;

using 				glm::value_ptr;
using				glm::radians;
using 				glm::distance;