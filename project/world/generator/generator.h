#pragma once

#include "FastNoise.h"

#include "common/aliases.h"
#include "common/glm.h"
#include "engine/object/unique_object.h"

class 					chunk;

class					generator : public unique_object<generator>
{
public :
						generator();
						~generator() override = default;


	static void			generate(const shared_ptr<chunk> &chunk);

	int 				height_level(const vec3 &position);

private :

	FastNoise			noise;
};


