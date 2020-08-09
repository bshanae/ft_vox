#include "object.h"

#include "application.h"

void				object::connect_to_application()
{
	application::instance()->new_objects.emplace_back(layout, shared_from_this());
}