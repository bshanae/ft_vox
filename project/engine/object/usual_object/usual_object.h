#pragma once

#include "engine/core/core.h"
#include "engine/object/object/object.h"

namespace					engine
{
	template				<typename, typename>
	class					inheritor_object;

	template				<typename>
	class					usual_object;
}

template					<typename final_type>
class						engine::usual_object : public object
{
	template				<typename, typename>
	friend class 			engine::inheritor_object;

public :

	using					object::state;

							usual_object() = default;
							~usual_object() override = default;

	template				<typename ...args_type>
	static
	shared_ptr<final_type>	create(args_type &&...args)
	{
		auto				final = make_shared<final_type>(args...);
		auto 				object = dynamic_pointer_cast<usual_object>(final);

		assert(object != nullptr and "Incorrect object usage");
		object->create_implementation();
		object->connect_to_core();
		object->state.value = state::uninitialized;
		return (final);
	}

	void					destroy() final
	{
		if (state == state::active)
			deactivate();
		destroy_implementation();
		should_be_destroyed = true;
	}

	void					activate() final
	{
		activate_implementation();
		state.value = state::active;
	}

	void					deactivate() final
	{
		deactivate_implementation();
		state.value = state::inactive;
	}

protected :

	bool 					automatic_activation = true;

	void 					render() override {}
	void 					update() override {}

	virtual void			create_implementation() {}
	virtual void			destroy_implementation() {}

	virtual void			initialize_implementation() {}
	virtual void			deinitialize_implementation() {}

	virtual void			activate_implementation() {}
	virtual void			deactivate_implementation() {}

private :

	void					initialize() final
	{
		initialize_implementation();
		state.value = state::initialized;
		if (automatic_activation)
			activate();
	}

	void					deinitialize() final
	{
		deinitialize_implementation();
		state.value = state::uninitialized;
	}
};