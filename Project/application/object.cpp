#include "object.h"

#include "application/application.h"

shared_ptr<object>		object::create()
{
	shared_ptr<object>	object;

	object = make_shared<class object>();
	object->create_internal();
	return (object);
}

void 					object::destroy()
{
	state = state::should_be_destroyed;
}

void					object::create_internal()
{
	connect_to_application();
	state = state::just_created;
}

void					object::start_internal()
{
	state = state::normal;
}

void					object::connect_to_application()
{
	application::instance()->new_objects.push_back(shared_from_this());
}