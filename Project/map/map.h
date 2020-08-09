#pragma once

#include "common/aliases.h"
#include "common/global.h"
#include "application/unique_object.h"
#include "map/chunk.h"
#include "map/block_id.h"

struct							map_settings
{
	static inline float			visibility_limit = 50.f;
	static inline float			cashing_limit = 50.f;
};

class							map : public unique_object<map>
{
	friend class 				chunk;

public :
								map();
								~map() override = default;

	static shared_ptr<chunk>	find_chunk(const vec3 &position);
	static optional<block_id>	find_block(const vec3 &position);

	static void 				insert_block(const vec3 &position, enum block::type type);
	static void 				remove_block(const vec3 &position);

private :

// ----------------------------	Chunks

	struct						vec3_comparator
	{
		bool					operator () (const vec3& left, const vec3 &right) const
		{
			return (left.x < right.x or (left.x == right.x and (left.y < right.y or (left.y == right.y and left.z < right.z))));
		}
	};

	using 						chunks_type = std::map<vec3, shared_ptr<chunk>, vec3_comparator>;
	chunks_type					chunks;

	static shared_ptr<chunk>	neighbor_chunk(const shared_ptr<chunk> &main, axis axis, sign sign);

// ----------------------------	Pivot

	vec3						pivot = vec3(0.f);

// ----------------------------	Object methods

	void						initialize_implementation() override;
	void						deinitialize_implementation() override;

	void						update() override;

// ----------------------------	Additional methods

	void						create_chunk_if_needed(const vec3 &position);
	void						destroy_chunk_if_needed(const shared_ptr<chunk> &chunk);

	void						create_chunk(const vec3 &position);
	void						destroy_chunk(const shared_ptr<chunk> &chunk);

	void 						try_build_chunk(const shared_ptr<chunk> &chunk);
};