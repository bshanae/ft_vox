#include "object.h"

#include "application/application.h"

std::shared_ptr<object>	object::create()
{
	auto				object = std::make_shared<::object>();

	application::instance()->objects.push_back(object);
	return (object);
}
