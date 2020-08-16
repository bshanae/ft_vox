#pragma once

#include "common/aliases.h"
#include "common/global.h"
#include "application/object.h"
#include "application/timer.h"

class 							window;
class 							object;

struct							application_settings
{
	static inline vec3			background = vec3(0.8f);
};

class 							application final : public global<application>
{
public :
								application();
								~application() override = default;

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

	friend void					object::connect_to_application();
};

