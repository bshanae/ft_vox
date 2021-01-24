#include "layout.h"

#include "engine/main/system/window/window.h"

using namespace 		engine;

						layout::layout(const string &name, int options) :
							name(name),
							options(options)
{}

const layout::data_type	&layout::get_objects() const
{
	return objects;
}

void 					layout::apply_options() const
{
	window::use_depth_test((options & (int)layout::use_depth_test) != 0);
}