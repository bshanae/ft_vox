#pragma once

#include "common/aliases.h"
#include "core/object/unique_object.h"
#include "world/block/block_id.h"
#include "world/chunk/chunk.h"
#include "world/world/world_settings.h"

class							world : public unique_object<world>
{
	friend class 				block_id;

	using						bool_property = property<read_only, bool, world>;

public :
								world();
								~world() override = default;

	static optional<block_id>	find_block(const vec3 &position);

	static void 				insert_block(const block_id &id, enum block::type type);
	static void 				remove_block(const block_id &id);

	static void					select_block(const block_id &id, block::face face);
	static void 				unselect_block();

	static inline bool_property	performing_initial_procedure;

private :

	struct						vec3_hasher
	{
		size_t					operator() (const vec3 &vector) const
		{
			size_t				h1 = hash<float>()(vector.x);
			size_t				h2 = hash<float>()(vector.y);
			size_t				h3 = hash<float>()(vector.z);

			return (h1 ^ (h2 << 1u)) ^ h3;
		}
	};

// ----------------------------	Attributes

	using						chunks_type = std::unordered_map<vec3, shared_ptr<chunk>, vec3_hasher>;

	chunks_type					chunks;

	chunks_type					new_chunks;
	vector<shared_ptr<chunk>>	old_chunks;

	queue<shared_ptr<chunk>>	chunks_with_postponed_build;

	using						sorted_chunks_type = multimap<float, shared_ptr<chunk>>;
	sorted_chunks_type			sorted_chunks;

// ----------------------------	Chunks

	static shared_ptr<chunk>	find_chunk(const vec3 &position);
	static shared_ptr<chunk>	find_new_chunk(const vec3 &position);

	static shared_ptr<chunk>	find_neighbor_chunk(const shared_ptr<chunk> &main, axis axis, sign sign);

// ----------------------------	Pivot

	vec3						pivot = vec3(0.f);

	float						distance(const vec3 &position);
	float						distance(const shared_ptr<chunk> &chunk);

// ----------------------------	Object methods

	void						initialize_implementation() override;
	void						deinitialize_implementation() override;

	void						update() override;
	void						render() override;

// ----------------------------	Initial procedure

	struct						initial_procedure_context
	{
		bool					first_call = true;
		bool					working = false;

		float					current_visibility = 5.f;
		float 					target_visibility = 0.f;
	}							initial_procedure_context;

	void						initial_procedure();

// ----------------------------	Additional methods

	void						create_chunk_if_needed(const vec3 &position);
	void						destroy_chunk_if_needed(const shared_ptr<chunk> &chunk);

	void						create_chunk(const vec3 &position);
	void						destroy_chunk(const shared_ptr<chunk> &chunk);

	void 						try_build_chunk(const shared_ptr<chunk> &chunk);

	void						rebuild_chunk(const shared_ptr<chunk> &chunk, const chunk::index &changed_block);
};