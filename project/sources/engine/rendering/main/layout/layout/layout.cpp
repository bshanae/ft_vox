#include "layout.h"

using namespace 		engine;

						layout::layout(const string &name, int options) :
							name(name),
							options(options)
{}

[[nodiscard]]
int 					layout::get_options() const
{
	return options;
}

[[nodiscard]]
const layout::data_type	&layout::get_objects() const
{
	return objects;
}