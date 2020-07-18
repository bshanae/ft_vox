#pragma once

#include "common/aliases.h"
#include "common/global.h"
#include "object/object.h"

class 							window;

class 							application final : public global<application>
{
public :
								application();
								~application() override = default;

	static void					execute();

private :

	shared_ptr<window>			window;

	vector<shared_ptr<object>>	objects;

	void						process_creating();
	void						process_destroying();

	void						process_updating();
	void						process_rendering();

	friend shared_ptr<object>	object::create();
};