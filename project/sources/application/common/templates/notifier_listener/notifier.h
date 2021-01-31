#pragma once

#include "application/common/templates/notifier_listener/listener.h"
#include "application/common/imports/std.h"

template			<typename type>
class 				notifier
{
	using			listener_type = reference_wrapper<listener<type>>;
	using			listeners_type = list<listener_type>;

public :

	void			subscribe(listener<type> &listener)
	{
		listeners.push_back(reference_wrapper(listener));
	}

	void			unsubscribe(listener<type> &listener)
	{
		erase_if
		(
			listeners,
			[listener](const listener_type &item)
			{
				return &item.get() == &listener.get();
			}
		);
	}

protected :

	void			notify(const type &pocket)
	{
		for (const auto &listener : listeners)
			listener.get().notify(pocket);
	}

private :

	listeners_type	listeners;
};