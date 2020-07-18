#include "object_linker.h"

#include "application/application.h"

void				object_linker::link_to_application(const shared_ptr<object> &object)
{
	application::instance()->objects.push_back(object);
}
