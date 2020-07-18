#pragma once

#include "common/OpenGL.h"
#include "model/model.h"
#include "object/object.h"
#include "program/program.h"
#include "program/uniform.h"


class							renderer
{
	virtual void 				render(shared_ptr<object> o);
};

class							chunk : public object
{
public :
								chunk();
								~chunk() = default;

	static
	shared_ptr<chunk>			create()
	{
		auto					chunk = make_shared<class chunk>();

		link_to_application(chunk);
		return (chunk);
	}

	void						render() override;

#warning "Do we need this?"
								chunk(const chunk &other);
	chunk						&operator = (const chunk &other);

private :

	model						model;

	class						renderer
	{
	public :
								renderer()
		{
			program = make_unique<class program>(path_to_vertex_shader, path_to_fragment_shader);
			uniform_projection = program->create_uniform<mat4>("uniform_projection");
			uniform_view = program->create_uniform<mat4>("uniform_view");

			mat4 				projection;
			mat4 				view;

			projection = glm::perspective(glm::radians(30.f), 1280.f / 720.f, 0.f, 100.f);
			view = glm::lookAt(vec3(0), vec3(0, 0, -1), vec3(0, 1, 0));

//			program->bind(true);
//			uniform_projection.upload(projection);
//			uniform_view.upload(view);
//			program->bind(false);
		}
								~renderer() = default;

		void					render(const chunk &chunk)
		{
			const class model	&model = chunk.model;

			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			program->bind(true);
			model.bind(true);

			glDrawElements(GL_TRIANGLES, model.get_number_of_indices(), GL_UNSIGNED_INT, nullptr);

			model.bind(false);
			program->bind(false);
		}

	private :

		inline static const
		path					path_to_vertex_shader = "Project/resources/shaders/vertex.glsl";
		inline static const
		path					path_to_fragment_shader = "Project/resources/shaders/fragment.glsl";

		unique_ptr<program>		program;

		uniform<mat4>			uniform_projection;
		uniform<mat4>			uniform_view;
	};

	static inline
	unique_ptr<renderer>		renderer;
};