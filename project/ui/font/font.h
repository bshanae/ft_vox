#pragma once

#include "common/glm.h"
#include "common/freetype.h"
#include "engine/object/usual_object.h"

class 								symbol;

class								font : public enable_shared_from_this<font>
{
public :

	template						<typename ...args_type>
	static shared_ptr<font>			create(args_type &&...args)
	{
		shared_ptr<font>			pointer;

		pointer = make_shared<font>(args...);
		pointer->build_map();
		return (pointer);
	}
									font(const path &source, const int &width);
									~font() = default;

	shared_ptr<symbol>				find_symbol(char task) const;

private :

	void							build_map();
	shared_ptr<symbol>				build_symbol(char task);

	static constexpr int			size_of_map = 128;

	FT_Face							face = nullptr;
	map<char, shared_ptr<symbol>>	map;

	vec3							color = vec3(1.f);
};

