#pragma once

#include "common/aliases.h"
#include "application/object_linker.h"
#include "map/chunk.h"

class				map : public object
{
public :
					map()
	{
		const auto 	chunk_size = vec3(::chunk_size[0], ::chunk_size[1], ::chunk_size[2]);
		auto 		translation = vec3(0.f);

		for (auto &iterator : chunks)
		{
			translation = iterator->get_index().to_glm();
			translation *= chunk_size;

			iterator->get_value() = chunk::create();
			iterator->get_value()->set_translation(translation);
		}
	}
					~map() override = default;

	static
	shared_ptr<map>	create()
	{
		auto		map = make_shared<class map>();

		link_to_application(map);
		return (map);
	}

private :

	static
	inline
	constexpr int	size[3] = {2, 1, 2};

#warning "Don't use pointers?"
	using			chunks_type = array3<shared_ptr<chunk>, size[2], size[1], size[0]>;
	chunks_type		chunks;
};