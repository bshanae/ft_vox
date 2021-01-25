#include "debug.h"

#include "application/common/debug/defines.h"

#include <cstdio>
#include <cstdarg>

void				debug::log(const string &message)
{
	cout << "[Engine] " << message << endl;
}

void				debug::raise_error(string message, ...)
{
	va_list			arguments;

	va_start(arguments, message);
	write_error(message, arguments);
	va_end(arguments);

	exit(0);
}


void				debug::check_critical(bool statement, string message, ...)
{
	va_list			arguments;

	va_start(arguments, message);
	if (!statement)
		raise_error(message, arguments);
	va_end(arguments);
}


void				debug::raise_warning(string message, ...)
{
	va_list			arguments;

	va_start(arguments, message);
	write_warning(message, arguments);
	va_end(arguments);
}


bool				debug::check(bool statement, string message, ...)
{
	va_list			arguments;

	va_start(arguments, message);
	if (!statement)
		raise_warning(message, arguments);
	va_end(arguments);

	return statement;
}

void				debug::write_error(const string &message, va_list arguments)
{
	char			buffer[1024];
	string			format;

#if FT_DEBUG
	format = "[ft_vox warning] " + message;
#else
	format = "[ft_vox] Critical error : " + message;
#endif

	vsprintf(buffer, format.c_str(), arguments);
	cerr << buffer << endl;
}

void				debug::write_warning(const string &message, va_list arguments)
{
	char			buffer[1024];
	string			format;

#if FT_DEBUG
	format = "[ft_vox warning] " + message;
#endif

	vsprintf(buffer, format.c_str(), arguments);
	cerr << buffer << endl;
}