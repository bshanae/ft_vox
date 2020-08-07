#pragma once

#include "common/aliases.h"
#include "common/global.h"
#include "application/object.h"

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

	static void					execute();

private :

	using						objects_container_type = vector<shared_ptr<object>>;

	objects_container_type		objects;
	objects_container_type		new_objects;

	void						process_input();

	void						process_creating();
	void						process_destroying();

	void						process_updating();
	void						process_rendering();

	friend void					object::connect_to_application();
};

