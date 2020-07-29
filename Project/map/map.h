#pragma once

#include "common/aliases.h"
#include "common/global.h"
#include "application/unique_object.h"
#include "map/chunk.h"

struct							map_settings
{
	static inline float			visibility_limit = 40.f;
	static inline float			cashing_limit = 40.f;
};

class							map : public unique_object<map>
{
public :
								map();
								~map() override = default;
private :

	struct						vec3_comparator
	{
		bool					operator () (const vec3& left, const vec3 &right) const
		{
			return (left.x < right.x or (left.x == right.x and (left.y < right.y or (left.y == right.y and left.z < right.z))));
		}
	};

	vec3						pivot = vec3(0.f);

	using 						chunks_type = std::map<vec3, shared_ptr<chunk>, vec3_comparator>;
	chunks_type					chunks;

	void						start() override;
	void						update() override;

	static
	shared_ptr<chunk>			provide_neighbor_chunk(
									const shared_ptr<chunk> &main,
									axis axis,
									sign sign);

	void						create_chunk_if_needed(const vec3 &position);
	void						destroy_chunk_if_needed(const shared_ptr<chunk> &chunk);
};