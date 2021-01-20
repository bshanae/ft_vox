#include "object_manipulator.h"

#include "engine/core/object/object/object.h"

using namespace	engine;

void			object_manipulator::initialize(const shared_ptr<object> &object)
{
	object->when_initialized();
	object->state = object::state::initialized;
}

void			object_manipulator::deinitialize(const shared_ptr<object> &object)
{
	object->when_deinitialized();
	object->state = object::state::deinitialized;
}

void			object_manipulator::activate(const shared_ptr<object> &object)
{
	object->when_activated();
	object->state = object::state::activated;
}

void			object_manipulator::deactivate(const shared_ptr<object> &object)
{
	object->when_deactivated();
	object->state = object::state::deactivated;
}

void			object_manipulator::render(const shared_ptr<object> &object)
{
	object->when_rendered();
}

void			object_manipulator::update(const shared_ptr<object> &object)
{
	object->when_updated();
}