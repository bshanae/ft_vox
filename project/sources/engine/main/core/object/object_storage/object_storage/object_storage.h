#pragma once

#include "engine/main/core/object/object_storage/object_storage_event/object_storage_event.h"

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
	using			data_type = unordered_map<intptr_t, shared_ptr<object>>;

public :
					object_storage() = default;
					~object_storage() override;

	static void		add(const shared_ptr<object> &object);
	static void		remove(const shared_ptr<object> &object);
	static void 	clean();

private :

	data_type		objects;

	static void		do_remove(const shared_ptr<object> &object);
};


