#pragma once

#include "common/aliases.h"
#include "common/global.h"
#include "engine/object/object.h"

class 								window;
class 								object;

class 								core final : public global<core>
{
public :
									core();
									~core() override = default;

	static void 					register_layout(const string &key);

	static void						execute();

private :

	struct 							layout
	{
		explicit					layout(const string &name) : name(name) {}

		string 						name;
		vector<shared_ptr<object>>	objects;
	};

	vector<shared_ptr<object>>		new_objects;

	map<string, shared_ptr<layout>>	layouts;
	vector<shared_ptr<layout>>		layouts_order;

	void							process_input();

	void							process_creating();
	void							process_destroying();

	void							process_updating();
	void							process_rendering();

	friend void						object::connect_to_core();
};

