#pragma once

#include <vector>

#include "global.h"
#include "object/object.h"

class 										window;
class 										object;

class 										application final : public global<application>
{
public :
											application();
											~application() override = default;

	static void								execute();

private :

	std::shared_ptr<window>					window;

	std::vector<std::shared_ptr<object>>	objects;

	void									process_creating();
	void									process_destroying();

	void									process_updating();
	void									process_rendering();

	friend std::shared_ptr<object>			object::create();
};