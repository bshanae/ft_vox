#pragma once

#include "common/global.h"

namespace			application
{
	class 			application;
}

class				application::application : public global<application>
{
public :
					application();
					~application() override = default;

	static void 	execute();

private :

	static void		initialize_engine();

	static void		initialize_ui();

	static void		initialize_world();
	static void		initialize_texture_atlas();

	static void		initialize_player();
};


