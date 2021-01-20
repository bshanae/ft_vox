#pragma once

#include "application/common/imports/std.h"

namespace				engine
{
	class 				object;
	class				object_storage_event;
}

class					engine::object_storage_event
{
public :

	[[nodiscard]]
	shared_ptr<object>	get_object() const
	{
		return object;
	}

protected :

	explicit			object_storage_event(const shared_ptr<object> &object) : object(object) {}
	virtual				~object_storage_event() = default;

private :

	const
	shared_ptr<object>	object;
};