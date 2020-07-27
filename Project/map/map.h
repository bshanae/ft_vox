#pragma once

#include "common/aliases.h"
#include "common/global.h"
#include "application/unique_object.h"
#include "map/chunk.h"

class				map : public unique_object<map>
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

private :

	static
	inline
	constexpr int	size[3] = {1, 1, 1};

#warning "Don't use pointers?"
	using			chunks_type = array3<shared_ptr<chunk>, size[2], size[1], size[0]>;
	chunks_type		chunks;
};