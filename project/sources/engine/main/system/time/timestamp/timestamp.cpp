#include "timestamp.h"

using namespace		engine;

					timestamp::timestamp()
{
	value = (float)glfwGetTime();
}

float 				timestamp::get_value() const
{
	return value;
}

					timestamp::operator float () const
{
	return get_value();
}

float				timestamp::operator - (const timestamp &that) const
{
	return this->value - that.value;
}

ostream				&engine::operator << (ostream &stream, const timestamp &timestamp)
{
	stream << (float)timestamp << " s.";
	return stream;
}

string				engine::to_string(const timestamp &timestamp)
{
	return std::to_string((float)timestamp) + " s.";
}