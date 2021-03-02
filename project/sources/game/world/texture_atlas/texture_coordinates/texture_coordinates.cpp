#include "texture_coordinates.h"

using namespace		game;

texture_coordinates	&texture_coordinates::set_all(const ivec2 &value)
{
	_left = value;
	_right = value;
	_top = value;
	_bottom = value;
	_back = value;
	_front = value;

	return *this;
}

texture_coordinates	&texture_coordinates::set_left(const ivec2 &value)
{
	_left = value;
	return *this;
}

texture_coordinates	&texture_coordinates::set_right(const ivec2 &value)
{
	_right = value;
	return *this;
}

texture_coordinates	&texture_coordinates::set_top(const ivec2 &value)
{
	_top = value;
	return *this;
}

texture_coordinates	&texture_coordinates::set_bottom(const ivec2 &value)
{
	_bottom = value;
	return *this;
}

texture_coordinates	&texture_coordinates::set_back(const ivec2 &value)
{
	_back = value;
	return *this;
}

texture_coordinates	&texture_coordinates::set_front(const ivec2 &value)
{
	_front = value;
	return *this;
}

ivec2 				texture_coordinates::get_left() const
{
	return _left;
}

ivec2 				texture_coordinates::get_right() const
{
	return _right;
}

ivec2 				texture_coordinates::get_top() const
{
	return _top;
}

ivec2 				texture_coordinates::get_bottom() const
{
	return _bottom;
}

ivec2 				texture_coordinates::get_back() const
{
	return _back;
}

ivec2 				texture_coordinates::get_front() const
{
	return _front;
}