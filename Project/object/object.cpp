#include "object.h"

#include "application/application.h"

shared_ptr<object>	object::create()
{
	auto			object = make_shared<::object>();

	application::instance()->objects.push_back(object);
	return (object);
}
