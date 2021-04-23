#pragma once

#include "engine/main/core/object/object_storage/object_storage/object_storage.h"
#include "engine/main/core/object/object_manipulator/object_manipulator.h"

#include "application/common/debug/debug.h"
#include "application/common/imports/std.h"

namespace						engine
{
	class 						object;

	template					<typename>
	class 						object_constructor;
}

template						<typename type>
class 							engine::object_constructor
{
public :

	template					<typename ...args_type>
	static shared_ptr<type>		create(args_type &&...args)
	{
		shared_ptr<type>		instance;
		shared_ptr<object>		instance_as_object;

		instance = make_shared<type>(args...);

		instance_as_object = dynamic_pointer_cast<object>(instance);
		debug::check_critical(instance_as_object != nullptr, "[object_constructor] Target type doesn't derive from engine::object");

		object_storage::add(instance_as_object);
		object_manipulator::initialize(instance);
		return instance;
	}
};