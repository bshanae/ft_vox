#pragma once

#include "application/common/imports/std.h"

namespace					game
{
	class					chunk_workspace;
	class					chunk_generation_task;
}

class						game::chunk_generation_task
{
public :
							chunk_generation_task() = delete;
	virtual					~chunk_generation_task();

	bool 					is_waiting() const;
	bool 					is_processing() const;
	bool 					is_finished() const;

	void 					launch(chunk_workspace &workspace);
	void 					wait();

protected :

	explicit				chunk_generation_task(bool is_async);
	virtual void 			do_launch(chunk_workspace &workspace) = 0;

private :

	enum					state
	{
		waiting,
		processing,
		finished
	};

	const bool 				is_async;
	enum state				state;
	optional<future<void>>	future;

	void 					do_process_and_switch_states(chunk_workspace &workspace);
};


