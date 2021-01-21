#pragma once

#include "engine/main/core/object/object/object.h"
#include "engine/main/core/object/object_storage/object_storage_event/object_storage_event.h"

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

	static void					execute();

private :

	stack<shared_ptr<object>>	added_objects;
	stack<shared_ptr<object>>	removed_objects;

	static void					process_input();

	static void					process_activation();
	static void					process_updating();
	static void					process_rendering();
};