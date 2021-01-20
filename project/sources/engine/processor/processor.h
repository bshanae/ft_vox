#pragma once

#include "engine/core/object/object/object.h"
#include "engine/core/object/object_storage/object_storage_event/object_storage_event.h"

#include "application/common/templates/singleton/singleton.h"
#include "application/common/templates/notifier_listener/listener.h"
#include "application/common/imports/std.h"

namespace						engine
{
	class 						object;
	class 						layout;
	class 						window;

	class 						processor;
}

class 							engine::processor final : public singleton<processor>
{
public :
								processor();
								~processor() override = default;

	void						execute();

private :

	stack<shared_ptr<object>>	added_objects;
	stack<shared_ptr<object>>	removed_objects;

	void						process_input();

	void						process_activation();
	void						process_updating();
	void						process_rendering();
};