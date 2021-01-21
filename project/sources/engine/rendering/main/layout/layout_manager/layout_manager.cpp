#include "layout_manager.h"

#include "engine/core/object/object_storage/object_storage/object_storage.h"
#include "engine/core/object/object_storage/object_storage_event/object_was_added.h"
#include "engine/core/object/object_storage/object_storage_event/object_was_removed.h"

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

	assert("[layout_manager::add] Layout not found");
	return nullptr;
}

void 							layout_manager::when_constructed()
{
	object_storage::get_instance()->subscribe(get_instance());
}

void							layout_manager::when_notified(const shared_ptr<const object_storage_event> &pocket)
{
	if (dynamic_pointer_cast<const object_was_added>(pocket))
		get_instance()->add(pocket->get_object());
	else if (dynamic_pointer_cast<const object_was_removed>(pocket))
		get_instance()->remove(pocket->get_object());
	else
		assert(0);
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

	assert("[layout_manager::add] Can't find layout");
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

	assert("[layout_manager::add] Can't find layout");
}