#include "object_storage.h"

#include "engine/main/core/object/object_manipulator/object_manipulator.h"
#include "engine/main/core/object/object_storage/object_storage_event/object_was_added.h"
#include "engine/main/core/object/object_storage/object_storage_event/object_was_removed.h"

using namespace		engine;

					object_storage::~object_storage()
{
	for (const auto &object : objects)
		object_manipulator::deinitialize(object.second);
}

void				object_storage::add(const shared_ptr<object> &object)
{
	auto			instance = get_instance();

	instance->objects.emplace((intptr_t)object.get(), object);
	instance->notify(make_shared<object_was_added>(object));
}

void				object_storage::remove(const shared_ptr<object> &object)
{
	auto			instance = get_instance();

	instance->objects.erase((intptr_t)object.get());
	instance->notify(make_shared<object_was_removed>(object));
	object_manipulator::deinitialize(object);
}