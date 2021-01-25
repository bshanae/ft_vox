#pragma once

#include "application/common/imports/std.h"

class				debug
{
public :
					debug() = delete;

	static void 	log(const string &message);

	static void		raise_error(string message, ...);
	static void		check_critical(bool statement, string message, ...);

	static void		raise_warning(string message, ...);
	static bool		check(bool statement, string message, ...);

private :

	static void 	write_error(const string &message, va_list arguments);
	static void 	write_warning(const string &message, va_list arguments);
};