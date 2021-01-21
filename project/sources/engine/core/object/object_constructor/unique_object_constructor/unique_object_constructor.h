#pragma once

#include "engine/core/object/object_storage/object_storage/object_storage.h"
#include "engine/core/object/object_manipulator/object_manipulator.h"

#include "application/common/imports/std.h"

namespace				engine
{
	class 				object;

	template			<typename>
	class 				unique_object_constructor;
}

template				<typename type>
class 					engine::unique_object_constructor : public singleton<type>
{
protected :

	void				when_constructed() final
	{
		auto 			instance = singleton<type>::get_instance();

		object_storage::add(instance);
		object_manipulator::initialize(instance);
	}
};