#include "object.h"

#include "core/core/core.h"

void				object::connect_to_core()
{
	core::instance()->new_objects.emplace_back(layout, shared_from_this());
}