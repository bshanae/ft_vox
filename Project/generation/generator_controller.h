#pragma once

#include "common/aliases.h"
#include "common/global.h"
#include "generation/generator.h"
#include "generation/plain_generator.h"

class						generator_controller : public global<generator_controller>
{

  friend class				application;

public :
							generator_controller() = default;
							~generator_controller() override = default;

	enum class				generator_type
	{
		plain = 0
	};

private :

	using 					generators_type = std::map<generator_type, shared_ptr<generator>>;
	generators_type			generators;

	void					initializer(std::shared_ptr<generator_controller> pointer) override
	{
		pointer->generators[generator_type::plain] = make_shared<plain_generator>();
	}
};

