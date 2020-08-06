#pragma once

#include "common/aliases.h"

template 				<typename type>
class					property_read_functionality
{
	template			<typename, typename, typename>
	friend class 		property;

protected :

	explicit			property_read_functionality(const type &target) :
							target(target)
	{
		getter = [this](){ return (this->target); };
	}

						operator type () const
	{
		assert(getter != nullptr and "Getter is nullptr");
		return (getter());
	}

	const type			&operator * () const
	{
		assert(is_direct_access_allowed and "Direct access is prohibited");
		return (target);
	}

	const type			*operator -> () const
	{
		assert(is_direct_access_allowed and "Direct access is prohibited");
		return (addressof(target));
	}

protected :

	using 				getter_type = function<type()>;
	getter_type			getter = nullptr;

	bool 				is_direct_access_allowed = true;

private :

	const type			&target;
};

template 				<typename type>
class					property_write_functionality
{
	template			<typename, typename, typename>
	friend class 		property;

protected :

	explicit			property_write_functionality(type &target) : target(target)
	{
		setter = [this](const type &value){ this->target = value; };
	}

	void				operator = (const type &value)
	{
		assert(setter != nullptr and "Setter is nullptr");
		setter(value);
	}

	type				&operator * ()
	{
		assert(is_direct_access_allowed and "Direct access is prohibited");
		return (target);
	}

	type				*operator -> ()
	{
		assert(is_direct_access_allowed and "Direct access is prohibited");
		return (addressof(target));
	}

protected :

	using 				setter_type = function<void(const type &)>;
	setter_type			setter = nullptr;

	bool 				is_direct_access_allowed = true;

private :

	type				&target;
};

template 				<typename type, typename owner_type>
class 					property_complete_functionality :
							public property_read_functionality<type>,
							public property_write_functionality<type>
{
	template			<typename, typename, typename>
	friend class 		property;

public :
						property_complete_functionality() :
							property_read_functionality<type>(value),
							property_write_functionality<type>(value)
						{}

protected :

	type				value;

	void 				prohibit_direct_access()
	{
		property_read_functionality<type>::is_direct_access_allowed = false;
		property_write_functionality<type>::is_direct_access_allowed = false;
	}
};

class 					read_only;
class 					write_only;
class 					read_write;

template				<typename access, typename type, typename owner_type>
class					property
{};

template				<typename type, typename owner_type>
class					property<read_only, type, owner_type> : public property_complete_functionality<type, owner_type>
{
	friend				owner_type;

public :

	using				property_read_functionality<type>::operator type;
	using				property_read_functionality<type>::operator ->;
	using				property_read_functionality<type>::operator *;

private :

	using				property_write_functionality<type>::operator =;
};

template				<typename type, typename owner_type>
class					property<write_only, type, owner_type> : public property_complete_functionality<type, owner_type>
{
	friend				owner_type;

public :

	using				property_write_functionality<type>::operator =;
	using				property_write_functionality<type>::operator ->;
	using				property_write_functionality<type>::operator *;

private :

	using				property_read_functionality<type>::operator type;
};

template				<typename type, typename owner_type>
class					property<read_write, type, owner_type> : public property_complete_functionality<type, owner_type>
{
	friend				owner_type;

public :

	using				property_write_functionality<type>::operator =;
	using				property_write_functionality<type>::operator ->;
	using				property_write_functionality<type>::operator *;

	using				property_read_functionality<type>::operator type;
};