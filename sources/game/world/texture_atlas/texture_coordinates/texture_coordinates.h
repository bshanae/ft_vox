#pragma once

#include "application/common/imports/glm.h"

namespace				game
{
	class				texture_coordinates;
}

class					game::texture_coordinates
{
public :
						texture_coordinates() = default;
						~texture_coordinates() = default;

	texture_coordinates	&set_all(const ivec2 &value);

	texture_coordinates	&set_left(const ivec2 &value);
	texture_coordinates	&set_right(const ivec2 &value);
	texture_coordinates	&set_top(const ivec2 &value);
	texture_coordinates	&set_bottom(const ivec2 &value);
	texture_coordinates	&set_back(const ivec2 &value);
	texture_coordinates	&set_front(const ivec2 &value);

	ivec2 				get_left() const;
	ivec2 				get_right() const;
	ivec2 				get_top() const;
	ivec2 				get_bottom() const;
	ivec2 				get_back() const;
	ivec2 				get_front() const;

private :

	ivec2 				_left;
	ivec2 				_right;
	ivec2 				_top;
	ivec2 				_bottom;
	ivec2 				_back;
	ivec2 				_front;
};


