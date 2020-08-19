#pragma once

#include "common/aliases.h"
#include "common/global.h"
#include "core/object/object.h"

class 							window;
class 							object;

class 							core final : public global<core>
{
public :
								core();
								~core() override = default;

	static void 				register_layout(const string &key);

	static void					execute();

private :

	using						new_objects_type = vector<pair<string, shared_ptr<object>>>;
	using						layouts_type = map<string, vector<shared_ptr<object>>>;

	new_objects_type			new_objects;
	layouts_type				layouts;

	void						process_input();

	void						process_creating();
	void						process_destroying();

	void						process_updating();
	void						process_rendering();

	friend void					object::connect_to_core();
};

