#pragma once

#include "engine/core/object/usual_object/usual_object.h"

namespace					engine
{
	template				<typename, typename>
	class					inheritor_object;
}

template 					<typename child_type, typename parent_type>
class 						engine::inheritor_object : public parent_type
{
	static_assert(is_base_of<usual_object<parent_type>, parent_type>::value, "Parent should derive from usual object class");

public :

	template				<typename ...args_type>
	static
	shared_ptr<child_type>	create(args_type &&...args)
	{
		auto				final = make_shared<child_type>(args...);
		auto 				object = dynamic_pointer_cast<usual_object<parent_type>>(final);

		assert(object and "Incorrect object usage");
		object->create_implementation();
		object->connect_to_core();
		object->state.value = object::uninitialized;
		return (final);
	}

};