#include "object.h"

#include "engine/core/core.h"

using namespace 	engine;

void				object::connect_to_core()
{
	core::instance()->new_objects.push_back(shared_from_this());
}