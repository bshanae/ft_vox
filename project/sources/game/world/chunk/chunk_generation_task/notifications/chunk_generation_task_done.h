#pragma once

#include "game/world/chunk/chunk_generation_task/notifications/chunk_generation_task_notification.h"

namespace			game
{
	struct 			chunk_generation_task_done : public chunk_generation_task_notification {};
}