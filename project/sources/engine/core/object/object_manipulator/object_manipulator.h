#pragma once

#include "application/common/templates/singleton/singleton.h"
#include "application/common/imports/std.h"

namespace			engine
{
	class 			object;
	class 			object_manipulator;

	class 			processor;
}

class				engine::object_manipulator
{
	friend class 	object;

	template		<typename>
	friend class 	object_constructor;

	template		<typename>
	friend class 	unique_object_constructor;

	friend class 	object_storage;

private :

	static void		initialize(const shared_ptr<object> &object);
	static void		deinitialize(const shared_ptr<object> &object);

	static void		activate(const shared_ptr<object> &object);
	static void		deactivate(const shared_ptr<object> &object);

	static void		render(const shared_ptr<object> &object);
	static void		update(const shared_ptr<object> &object);
};