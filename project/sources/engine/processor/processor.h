#pragma once

#include "application/common/imports/std.h"
#include "application/common/classes/singleton.h"

#include "engine/core/object/object/object.h"

namespace							engine
{
	class 							object;
	class 							layout;
	class 							window;

	class 							processor;
}

class 								engine::processor final : public singleton<processor>
{
public :
									processor();
									~processor() override = default;

	static void 					register_layout(const string &key, int options = 0);

	static void						execute();

private :

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

