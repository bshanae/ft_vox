#pragma once

#include "application/common/templates/notifier_listener/listener.h"
#include "application/common/imports/std.h"

template			<typename type>
class 				notifier
{
	using			listeners_type = list<shared_ptr<listener<type>>>;

public :

	void			subscribe(const shared_ptr<listener<type>> &listener)
	{
		listeners.push_back(listener);
	}

	void			unsubscribe(const shared_ptr<listener<type>> &listener)
	{
		erase_if
		(
			listeners,
			[listener](const shared_ptr<::listener<type>> &item)
			{
				return item.get() == listener.get();
			}
		);
	}

protected :

	void			notify(const shared_ptr<const type> &pocket)
	{
		for (const auto &listener : listeners)
			listener->notify(pocket);
	}

private :

	listeners_type	listeners;
};