#pragma once

#include "common/glm.h"
#include "common/property.h"
#include "engine/object/usual_object.h"

class 				font;

class				text : public usual_object<text>
{
public :
					text();
					~text() override = default;

					property<read_write, string, text>
					string;

					property<read_write, ivec2, text>
					position;

					property<read_write, shared_ptr<font>, text>
					font;

					property<read_only, ivec2, text>
					size;
private :

	void			render() override;

	void			recalculate_size();
};


