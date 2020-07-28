#pragma once

#include "common/aliases.h"
#include "common/global.h"
#include "application/object.h"

class 							window;
class 							object;

class 							application final : public global<application>
{
public :
								application();
								~application() override = default;

	static void					execute();

private :

	vector<shared_ptr<object>>	objects;

	void						process_input();

	void						process_creating();
	void						process_destroying();

	[[deprecated]]
	void						process_early_updating();

	void						process_updating();
	void						process_rendering();

	friend void 				object::link_to_application();
};

