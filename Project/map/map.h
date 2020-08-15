#pragma once

#include "common/aliases.h"
#include "common/global.h"
#include "application/unique_object.h"
#include "map/block_id.h"
#include "map/chunk.h"
#include "map/map_settings.h"

class							map : public unique_object<map>
{
	friend class 				block_id;

public :
								map();
								~map() override = default;

	static optional<block_id>	find_block(const vec3 &position);

	static void 				insert_block(const vec3 &position, enum block::type type);
	static void 				remove_block(const vec3 &position);

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

	using						sorted_models_type = multimap<float, shared_ptr<model>>;
	sorted_models_type			sorted_models;

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

	struct						initial_procedure_settings
	{
		static inline
		const float				start_visibility = 5.f;

		static inline
		const float				visibility_progress = 1.f;
	};

	struct						initial_procedure_context
	{
		bool					first_call = true;
		bool					working = false;

		float					current_visibility = 0.f;
		float 					target_visibility = 0.f;
	}							initial_procedure_context;

	void						initial_procedure();

// ----------------------------	Additional methods

	void						create_chunk_if_needed(const vec3 &position);
	void						destroy_chunk_if_needed(const shared_ptr<chunk> &chunk);

	void						create_chunk(const vec3 &position);
	void						destroy_chunk(const shared_ptr<chunk> &chunk);

	void 						try_build_chunk(const shared_ptr<chunk> &chunk);
};