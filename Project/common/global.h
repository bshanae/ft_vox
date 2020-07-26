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
		if constexpr (not std::is_base_of<global<final_type>, final_type>::value)
			assert(false and "Bad usage of global class");

		assert(pointer == nullptr and "Global instance is already initialized");
		pointer = std::make_shared<final_type>();
		std::static_pointer_cast<global>(pointer)->initializer(pointer);
	}

protected :

	static auto					instance()
	{
		assert(pointer != nullptr and "Global instance is not initialized");
		return (pointer);
	}

	virtual void				initializer(std::shared_ptr<final_type>)
	{}

private :

	static
	inline
	std::shared_ptr<final_type>	pointer;
};