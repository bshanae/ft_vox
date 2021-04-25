#pragma once

#include "application/common/templates/notifier_and_listener/listener.h"
#include "application/common/imports/std.h"
#include "application/common/defines.h"
#include "application/common/debug/debug.h"

template			<typename type>
class 				notifier
{
public :

	void			subscribe(listener<type> &listener)
	{
		listeners.emplace((size_t)&listener, ref(listener));
	}

	void			unsubscribe(listener<type> &listener)
	{
		listeners.erase((size_t)&listener);
	}

#if FT_VOX_DEBUG
	void			check_number_of_listeners(int expected) const
	{
		debug::check_critical(listeners.size() == expected, "[notifier] Validation on number of listeners failed");
	}
#endif

protected :

	void			notify(const type &notification)
	{
		for (const auto &[ptr, listener] : listeners)
			listener.get().notify(notification);
	}

private :

	using			listeners_type = unordered_map<size_t, reference_wrapper<listener<type>>>;
	listeners_type	listeners;
};