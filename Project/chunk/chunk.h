#pragma once

#include "common/OpenGL.h"
#include "model.h"
#include "object/object.h"

#include "chunk/block.h"

class							chunk :
									public object,
									public model
{
	friend class 				renderer;

public :

								chunk();
								~chunk() override = default;

	static
	shared_ptr<chunk>			create()
	{
		auto					chunk = make_shared<class chunk>();

		link_to_application(chunk);
		return (chunk);
	}

	void						render() override;

private :

//	static constexpr int		size[3] = {16, 256, 16};
	static constexpr int		size[3] = {4, 4, 4};

	using						blocks_type = array<array<array<block, size[2]>, size[1]>, size[0]>;

	blocks_type					blocks;
	shared_ptr<model>			model;

	vector<float>				vertices;
	vector<GLuint>				indices;

	enum class					direction
	{
		begin,
		left,
		right,
		bottom,
		top,
		back,
		front,
		end
	};

	void						build_model();
	void						build_block(ivec3 index);
	void						build_quad(direction type, ivec3 index);

	static ivec3				get_neighbor_block(ivec3 index, direction direction);
	static bool					does_block_exist(ivec3 index);
	bool						is_block_empty(ivec3 index);
};