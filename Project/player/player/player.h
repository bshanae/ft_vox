#pragma once

#include "core/object/unique_object.h"

class				player : public unique_object<player>
{
public :
					player();
					~player() override = default;
private :

	void			update() override;

	void 			process_movement();
	void 			process_interaction();
};


