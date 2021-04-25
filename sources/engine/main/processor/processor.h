#pragma once

#include "application/common/templates/singleton/singleton.h"
#include "application/common/templates/notifier_and_listener/listener.h"
#include "application/common/imports/std.h"

#include "engine/main/core/object/object/object.h"
#include "engine/main/core/object/object_storage/object_storage_event/object_storage_event.h"

namespace			engine
{
	class 			object;
	class 			layout;
	class 			window;

	class 			processor;
}

class 				engine::processor final : public singleton<processor>
{
public :
					processor() = default;
					~processor() override = default;

	static void		execute();

private :

	static void		process_input();

	static void		process_activation();
	static void		process_updating();
	static void		process_rendering();
};