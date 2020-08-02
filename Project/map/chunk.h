#pragma once

#include "common/OpenGL.h"
#include "common/aliases.h"
#include "common/array3.h"
#include "application/object.h"
#include "map/model.h"

#include "map/block.h"

struct						chunk_settings
{
	static
	constexpr int			size[3] = {4, 4, 4};

	static inline
	const vec3				size_as_vector = vec3(size[0], size[1], size[2]);
};

class						chunk :
								public object,
								public model,
								private array3<block, chunk_settings::size[0], chunk_settings::size[1], chunk_settings::size[2]>
{
	friend class			chunk_editor;
	friend class 			map;
	friend class 			renderer;

public :

	using					index = array3<block, chunk_settings::size[0], chunk_settings::size[1], chunk_settings::size[2]>::index;

public :

	explicit				chunk(const vec3 &position);
							~chunk() override = default;

	template				<typename ...args_type>
	static
	shared_ptr<chunk>		create(args_type &&...args)
	{
		auto				chunk = make_shared<class chunk>(args...);

		create_internal(chunk);
		return (chunk);
	}

	[[nodiscard]] vec3		get_position()
	{
		return (position);
	}

	[[nodiscard]] vec3		center()
	{
		return (position + chunk_settings::size_as_vector / 2.f);
	}


private :

	vec3 					position = vec3(0);

	shared_ptr<model>		model;

	vector<GLfloat>			vertices;
	vector<GLfloat>			texture_coordinates;
	vector<GLuint>			indices;

	void					render() override;

	bool					is_built = false;

	void					build_model();
	void					build_block(const index &index);
	void					build_quad(axis axis, sign sign, const index &index);

	template				<typename type>
	void					append_to_vector(vector<type> &target, const vector<type> &source)
	{
		target.insert(target.end(), source.begin(), source.end());
	}

	using 					neighbor_provider_type = function<shared_ptr<chunk>(const shared_ptr<chunk> &, axis, sign)>;
	static
	inline
	neighbor_provider_type	neighbor_provider = nullptr;
};