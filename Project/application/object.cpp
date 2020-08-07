#include "object.h"

#include "application.h"

void				object::connect_to_application()
{
	application::instance()->new_objects.push_back(shared_from_this());
}