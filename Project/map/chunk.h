#pragma once

#include "common/OpenGL.h"
#include "common/array3.h"
#include "model.h"
#include "object/object.h"

#include "map/block.h"

#warning "Create settings module"
static constexpr int			chunk_size[3] = {4, 4, 4};


class							chunk :
									public object,
									public model,
									private array3<block, chunk_size[0], chunk_size[1], chunk_size[2]>
{
	friend class				chunk_generator;
	friend class 				map;
	friend class 				renderer;

public :

	using						index = array3<block, chunk_size[0], chunk_size[1], chunk_size[2]>::index;

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

	shared_ptr<model>			model;

	vector<float>				vertices;
	vector<GLuint>				indices;

	void						build_model();
	void						build_block(const index &index);
	void						build_quad(axis axis, sign sign, const index &index);
};