#pragma once

#include "common/aliases.h"
#include "common/glm.h"
#include "engine/object/unique_object.h"

class 							chunk;

class							generator : public unique_object<generator>
{
public :
								generator() = default;
								~generator() = default;


	static shared_ptr<chunk>	generate(const vec3 &position);

private :
};


