#pragma once

#include "common/aliases.h"
#include "common/global.h"

class 							window;
class 							object;

class 							application final : public global<application>
{
	friend class 				object_linker;

public :
								application();
								~application() override = default;

	static void					execute();

private :

	vector<shared_ptr<object>>	objects;

	void						process_creating();
	void						process_destroying();

	void						process_updating();
	void						process_rendering();
};

