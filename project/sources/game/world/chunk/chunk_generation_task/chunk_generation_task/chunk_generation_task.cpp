#include "chunk_generation_task.h"

using namespace				game;

							chunk_generation_task::~chunk_generation_task()
{
	wait();
}

bool 						chunk_generation_task::is_waiting() const
{
	return state == waiting;
}

bool 						chunk_generation_task::is_processing() const
{
	return state == processing;
}

bool 						chunk_generation_task::is_finished() const
{
	return state == finished;
}

void 						chunk_generation_task::launch(chunk_workspace &workspace)
{
	if (is_async)
		future = async(launch::async, &chunk_generation_task::do_process_and_switch_states, this, ref(workspace));
	else
		do_process_and_switch_states(workspace);
}

void 						chunk_generation_task::wait()
{
	if (future)
		future->wait();
}

							chunk_generation_task::chunk_generation_task(bool is_async) : is_async(is_async)
{
	state = waiting;
}

void 						chunk_generation_task::do_process_and_switch_states(chunk_workspace &workspace)
{
	state = processing;
	do_launch(workspace);
	state = finished;
}