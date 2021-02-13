#pragma once

#include "engine/main/rendering/layout/layout/layout.h"
#include "engine/main/core/object/object_storage/object_storage_event/object_storage_event.h"

#include "application/common/templates/singleton/singleton.h"
#include "application/common/templates/notifier_listener/listener.h"

namespace						engine
{
	class 						object;
	class 						layout_manager;
}

class							engine::layout_manager :
									public singleton<layout_manager>,
									public listener<object_storage_event>
{
	using						data_type = list<shared_ptr<layout>>;

public :

	static const data_type		&get_layouts();

	static void 				add(const string &name, int options = 0);
	static shared_ptr<layout>	find(const string &name);

private :

	static constexpr const char	*default_layout = "System";

	data_type					data;

	void 						when_constructed() override;
	void						when_notified(const object_storage_event &pocket) override;

	void						add(const shared_ptr<object> &object);
	void						remove(const shared_ptr<object> &object);
};