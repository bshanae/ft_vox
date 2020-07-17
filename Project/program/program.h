//#pragma once
//
//#include "engine/namespace.h"
//#include "engine/abstract/OpenGL_wrapper.h"
//#include "engine/program/uniform.h"
//
//class					engine::program::program : public engine::abstract::OpenGL_wrapper
//{
//public :
//						program(const path &vertex_source, const path &fragment_source);
//						~program() override;
//
//	void				use(bool state) override
//	{
//		glUseProgram(state ? object : 0);
//	}
//
//	template			<typename type>
//	[[nodiscard]] auto	make_uniform(const string &name)
//	{
//		return (uniform<type>(glGetUniformLocation(object, name.c_str())));
//	}
//};
