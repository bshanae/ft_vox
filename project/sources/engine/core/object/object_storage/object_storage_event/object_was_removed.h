#pragma once

#include "engine/core/object/object_storage/object_storage_event/object_storage_event.h"

namespace			engine
{
	class 			object;
	class			object_was_removed;
}

class				engine::object_was_removed : public object_storage_event
{
public :

	explicit		object_was_removed(const shared_ptr<engine::object> &object) : object_storage_event(object) {}
					~object_was_removed() override = default;
};