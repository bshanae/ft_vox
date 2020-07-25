#pragma once

#include "common/OpenGL.h"
#include "common/array3.h"
#include "model.h"
#include "object/object.h"

#include "map/block.h"

class							chunk :
									public object,
									public model
{
	friend class 				map;
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

	using						blocks_type = array3<block, size[0], size[1], size[2]>;

	blocks_type					blocks;
	shared_ptr<model>			model;

	vector<float>				vertices;
	vector<GLuint>				indices;

	ivec3 						position = ivec3(0, 0, 0);

	void						build_model();
	void						build_block(const blocks_type::index &index);
	void						build_quad(axis axis, sign sign, const blocks_type::index &index);
};