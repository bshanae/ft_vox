#include "layout_manager.h"

#include "application/common/utilities/type_utility.h"

#include "engine/main/core/object/object_storage/object_storage/object_storage.h"
#include "engine/main/core/object/object_storage/object_storage_event/object_was_added.h"
#include "engine/main/core/object/object_storage/object_storage_event/object_was_removed.h"

using namespace					engine;

const layout_manager::data_type	&layout_manager::get_layouts()
{
	return get_instance()->data;
}

void		 					layout_manager::add(const string &name, int options)
{
	get_instance()->data.push_back(make_shared<layout>(name, options));
}

shared_ptr<layout>				layout_manager::find(const string &name)
{
	for (const auto &layout : get_instance()->data)
	{
		if (layout->name == name)
			return layout;
	}

	debug::raise_error("[layout_manager] Layout not found");
	return nullptr;
}

void 							layout_manager::when_constructed()
{
	add(default_layout);
	object_storage::get_instance()->subscribe(*this);
}

void							layout_manager::when_notified(const object_storage_event &pocket)
{
	if (type_utility::is_of_type<object_was_added>(pocket))
		get_instance()->add(pocket.get_object());
	else if (type_utility::is_of_type<object_was_removed>(pocket))
		get_instance()->remove(pocket.get_object());
	else
		debug::raise_warning("[layout_manager] Can't parse 'object_storage_event'");
}

void							layout_manager::add(const shared_ptr<object> &object)
{
	for (const auto &layout : data)
	{
		if (layout->name == object->get_layout())
		{
			layout->objects.push_back(object);
			return;
		}
	}

	debug::raise_warning("[layout_manager::add] Can't add object to layout '" + object->get_layout() + "'");
}

void							layout_manager::remove(const shared_ptr<object> &object)
{
	for (const auto &layout : data)
	{
		if (layout->name == object->get_layout())
		{
			erase(layout->objects, object);
			return;
		}
	}

	debug::raise_warning("[layout_manager::add] Can't remove object from layout '" + object->get_layout() + "'");
}