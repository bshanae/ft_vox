#pragma once

#include "application/unique_object.h"

class				player : public unique_object<player>
{
public :
					player();
					~player() override = default;
private :

	void			update() override;
};


