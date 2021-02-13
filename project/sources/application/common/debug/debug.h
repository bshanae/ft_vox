#pragma once

#include "application/common/imports/std.h"

class				debug
{
public :
					debug() = delete;

	static void 	log(const string &message);

	static void		raise_error(const string &message);
	static void		check_critical(bool statement, const string &message);

	static void		raise_warning(const string &message);
	static bool		check(bool statement, const string &message);
};