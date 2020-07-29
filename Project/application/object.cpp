#include "object.h"

#include "application/application.h"

shared_ptr<object>		object::create()
{
	shared_ptr<object>	object;

	object = make_shared<class object>();
	create_internal(object);
	return (object);
}

void 					object::destroy()
{
	state = state::should_be_destroyed;
}

void					object::create_internal(const shared_ptr<object> &object)
{
	object->connect_to_application();
	object->state = state::just_created;
}

void					object::connect_to_application()
{
	application::instance()->new_objects.push_back(shared_from_this());
}