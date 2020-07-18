#pragma once

#include <memory>

template						<typename final_type>
class							global
{
public :
								global() = default;
	virtual						~global() = default;

	static void					initialize()
	{
		pointer = std::make_shared<final_type>();
		std::static_pointer_cast<global>(pointer)->initializer(pointer);
	}

protected :

	static auto					instance()
	{
		assert(pointer != nullptr and "Global object is not initialized");
		return (pointer);
	}

	virtual void				initializer(std::shared_ptr<final_type>)
	{}

private :

	static
	inline
	std::shared_ptr<final_type>	pointer;
};