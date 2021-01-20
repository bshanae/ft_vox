#include "layout_storage.h"

#include "engine/core/object/object_storage/object_storage/object_storage.h"
#include "engine/core/object/object_storage/object_storage_event/object_was_added.h"
#include "engine/core/object/object_storage/object_storage_event/object_was_removed.h"

using namespace				engine;

layout_storage::data_type	&layout_storage::get_layouts()
{
	return get_instance()->data;
}

void		 				layout_storage::define(const string &name, int options)
{
	get_instance()->data[name] = make_shared<layout>(name, options);
}

shared_ptr<layout>			layout_storage::find(const string &name)
{
	auto						instance = get_instance();

	if (auto iterator = instance->data.find(name); iterator != instance->data.end())
		return iterator->second;

	assert("Layout not found");
	return nullptr;
}

void 						layout_storage::when_constructed()
{
	object_storage::get_instance()->subscribe(get_instance());
}

void						layout_storage::when_notified(const shared_ptr<const object_storage_event> &pocket)
{
	if (dynamic_pointer_cast<const object_was_added>(pocket))
		get_instance()->add(pocket->get_object());
	else if (dynamic_pointer_cast<const object_was_removed>(pocket))
		get_instance()->remove(pocket->get_object());
	else
		assert(0);
}

void						layout_storage::add(const shared_ptr<object> &object)
{
	try
	{
		data.at(object->get_layout())->objects.push_back(object);
	}
	catch (const std::out_of_range &exception)
	{
		assert("Can't add object into layout");
	}
}

void						layout_storage::remove(const shared_ptr<object> &object)
{
	try
	{
		erase(data.at(object->get_layout())->objects, object);
	}
	catch (const std::out_of_range &exception)
	{
		assert("Can't add object into layout");
	}
}