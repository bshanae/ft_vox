#pragma once

#include "engine/main/core/object/object_storage/object_storage_event/object_storage_event.h"

namespace			engine
{
	class 			object;
	class			object_was_added;
}

class				engine::object_was_added : public object_storage_event
{
public :

	explicit		object_was_added(const shared_ptr<engine::object> &object) : object_storage_event(object) {}
					~object_was_added() override = default;
};