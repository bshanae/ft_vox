#pragma once

#include "common/aliases.h"
#include "common/global.h"
#include "application/object.h"

class 							window;
class 							object;

struct							application_settings
{
	static inline vec3			background = vec3(0.2f);
};

class 							application final : public global<application>
{
public :
								application();
								~application() override = default;

	static void					execute();

private :

	vector<shared_ptr<object>>	objects;
	vector<shared_ptr<object>>	new_objects;

	void						process_input();

	void						process_creating();
	void						process_destroying();

	void						process_updating();
	void						process_rendering();

	friend void					object::connect_to_application();
};

