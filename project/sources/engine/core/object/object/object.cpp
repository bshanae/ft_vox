#include "object.h"

#include "engine/processor/processor.h"

using namespace 	engine;

void				object::connect_to_core()
{
	processor::get_instance()->new_objects.push_back(shared_from_this());
}