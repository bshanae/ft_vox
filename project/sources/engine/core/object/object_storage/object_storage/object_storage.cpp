#include "object_storage.h"

#include "engine/core/object/object_manipulator/object_manipulator.h"
#include "engine/core/object/object_storage/object_storage_event/object_was_added.h"
#include "engine/core/object/object_storage/object_storage_event/object_was_removed.h"

using namespace		engine;

					object_storage::~object_storage()
{
	for (const auto &object : objects)
		object_manipulator::deinitialize(object.second);
}

void				object_storage::add(const shared_ptr<object> &object)
{
	objects.emplace((intptr_t)object.get(), object);
	notify(make_shared<object_was_added>(object));
}

void				object_storage::remove(const shared_ptr<object> &object)
{
	objects.erase((intptr_t)object.get());
	notify(make_shared<object_was_removed>(object));
	object_manipulator::deinitialize(object);
}