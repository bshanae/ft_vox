#pragma once

#include "engine/rendering/main/layout/layout/layout.h"
#include "engine/core/object/object_storage/object_storage_event/object_storage_event.h"

#include "application/common/templates/singleton/singleton.h"
#include "application/common/templates/notifier_listener/listener.h"

namespace						engine
{
	class 						object;
	class 						layout_storage;
}

class							engine::layout_storage :
									public singleton<layout_storage>,
									public listener<object_storage_event>
{
	using						data_type = map<string, shared_ptr<layout>>;

public :

	static data_type			&get_layouts();

	static void 				define(const string &name, int options = 0);
	static shared_ptr<layout>	find(const string &name);

private :

	data_type					data;

	void 						when_constructed() override;
	void						when_notified(const shared_ptr<const object_storage_event> &pocket) override;

	void						add(const shared_ptr<object> &object);
	void						remove(const shared_ptr<object> &object);
};