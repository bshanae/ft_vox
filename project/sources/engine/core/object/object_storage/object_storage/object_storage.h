#pragma once

#include "engine/core/object/object_storage/object_storage_event/object_storage_event.h"

#include "application/common/templates/singleton/singleton.h"
#include "application/common/templates/notifier_listener/notifier.h"
#include "application/common/imports/std.h"

namespace			engine
{
	class 			object;
	class 			object_storage;
}

class				engine::object_storage final :
						public singleton<engine::object_storage>,
						public notifier<object_storage_event>
{
	template		<typename>
	friend class 	object_constructor;

	template		<typename>
	friend class 	unique_object_constructor;

	using			data_type = unordered_map<intptr_t, shared_ptr<object>>;

public :
					object_storage() = default;
					~object_storage();
private :

	void			add(const shared_ptr<object> &object);
	void			remove(const shared_ptr<object> &object);

	data_type		objects;
};


