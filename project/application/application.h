#pragma once

#include "common/global.h"

class				application : public global<application>
{
public :
					application();
					~application() override = default;

	static void 	execute();

private :

	void 			initialize_engine();

	void 			initialize_ui();

	void 			initialize_world();
	void			initialize_texture_atlas();

	void 			initialize_player();
};


