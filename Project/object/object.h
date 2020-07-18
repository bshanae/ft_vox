#pragma once

#include "common/OpenGL.h"
#include "common/aliases.h"
#include "application/application.h"
#include "application/object_linker.h"

class						object :
								public object_linker,
								public enable_shared_from_this<object>
{
	friend class 			application;

public :

							object() = default;
							~object() override = default;

	static
	shared_ptr<object>		create()
	{
		auto				object = make_shared<class object>();

		link_to_application(object);
		return (object);
	}


protected :

	virtual void 			render()
	{}

	virtual void 			update()
	{}

	vec3					position = vec3(0);
	vec3					rotation = vec3(0);

	mat4 					transformations = mat4(1);
};