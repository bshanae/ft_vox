#pragma once

#include "libraries/glm/glm/glm.hpp"
#include <memory>

class						object : public std::enable_shared_from_this<object>
{
public :

							object() = default;
							~object() = default;
	static
	std::shared_ptr<object>	create();

protected :

	virtual void 			render()
	{}

	virtual void 			update()
	{}

	glm::vec3				position = glm::vec3(0);
	glm::vec3				rotation = glm::vec3(0);

	glm::mat4 				transformations = glm::mat4(1);
};