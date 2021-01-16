#include "timestamp.h"

using namespace		engine;

					timestamp::timestamp()
{
	value = glfwGetTime();
}

float 				timestamp::get_value() const
{
	return value;
}

					timestamp::operator float () const
{
	return get_value();
}

float				timestamp::operator - (const timestamp &that)
{
	return this->value - that.value;
}

ostream				&operator << (ostream &stream, const timestamp &timestamp)
{
	stream << (float)timestamp << "s.";
	return stream;
}