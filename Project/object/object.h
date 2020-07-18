#pragma once

#include "common/OpenGL.h"
#include "common/aliases.h"

class					object : public enable_shared_from_this<object>
{
public :

						object() = default;
						~object() = default;
	static
	shared_ptr<object>	create();

protected :

	virtual void 		render()
	{}

	virtual void 		update()
	{}

	vec3				position = vec3(0);
	vec3				rotation = vec3(0);

	mat4 				transformations = mat4(1);
};