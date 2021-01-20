#include "object.h"

#include "engine/core/object/object_manipulator/object_manipulator.h"

using namespace 	engine;

					object::object()
{
	state = state::null;
}

void				object::activate()
{
	return object_manipulator::activate(shared_from_this());
}

void				object::deactivate()
{
	return object_manipulator::deactivate(shared_from_this());
}

void				object::render()
{
	return object_manipulator::render(shared_from_this());
}

void				object::update()
{
	return object_manipulator::update(shared_from_this());
}

enum object::state	object::get_state() const
{
	return state;
}

const string		&object::get_layout() const
{
	return layout;
}

void 				object::set_layout(const string &value)
{
	layout = value;
}