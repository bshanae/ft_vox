#pragma once

#include "engine/core/object/object_storage/object_storage/object_storage.h"

#include "application/common/imports/std.h"

template						<typename type>
class 							object_constructor
{
	template					<typename ...args_type>
	static shared_ptr<type>		create(args_type &&...args)
	{
		shared_ptr<type>		instance;
		auto					instance_as_object;

		instance = make_shared<type>(args...);

		instance_as_object = dynamic_pointer_cast<object>(instance);
		assert(instance_as_object != nullptr);
		object_storage::get_instance()->add(instance_as_object);

		return instance;
	}
};