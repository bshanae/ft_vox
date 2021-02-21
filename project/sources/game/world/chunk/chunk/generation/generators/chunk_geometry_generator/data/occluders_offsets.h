#pragma once

#include "game/world/chunk/chunk/chunk/chunk.h"

using namespace		game;

chunk::index		front_occluders_offsets[4][3] =
{
	{
		chunk::index(0, 1, +1),
		chunk::index(1, 0, +1),
		chunk::index(1, 1, +1)
	},

	{
		chunk::index(-1, 0, +1),
		chunk::index(0, +1, +1),
		chunk::index(-1, +1, +1)
	},

	{
		chunk::index(-1, 0, +1),
		chunk::index(0, -1, +1),
		chunk::index(-1, -1, +1)
	},

	{
		chunk::index(+1, 0, +1),
		chunk::index(0, -1, +1),
		chunk::index(+1, -1, +1)
	}
};

chunk::index		back_occluders_offsets[4][3] =
{
	{
		chunk::index(0, 1, -1),
		chunk::index(1, 0, -1),
		chunk::index(1, 1, -1)
	},

	{
		chunk::index(+1, 0, -1),
		chunk::index(0, -1, -1),
		chunk::index(+1, -1, -1)
	},

	{
		chunk::index(-1, 0, -1),
		chunk::index(0, -1, -1),
		chunk::index(-1, -1, -1)
	},

	{
		chunk::index(-1, 0, -1),
		chunk::index(0, +1, -1),
		chunk::index(-1, +1, -1)
	}
};

chunk::index		top_occluders_offsets[4][3] =
{
	{
		chunk::index(-1, +1, 0),
		chunk::index(0, +1, +1),
		chunk::index(-1, +1, +1)
	},

	{
		chunk::index(+1, +1, 0),
		chunk::index(0, +1, +1),
		chunk::index(+1, +1, +1)
	},

	{
		chunk::index(+1, +1, 0),
		chunk::index(0, +1, -1),
		chunk::index(+1, +1, -1)
	},

	{
		chunk::index(-1, +1, 0),
		chunk::index(0, +1, -1),
		chunk::index(-1, +1, -1)
	}
};

chunk::index		bottom_occluders_offsets[4][3] =
{
	{
		chunk::index(-1, -1, 0),
		chunk::index(0, -1, +1),
		chunk::index(-1, -1, +1)
	},

	{
		chunk::index(-1, -1, 0),
		chunk::index(0, -1, -1),
		chunk::index(-1, -1, -1)
	},

	{
		chunk::index(+1, -1, 0),
		chunk::index(0, -1, -1),
		chunk::index(+1, -1, -1)
	},

	{
		chunk::index(+1, -1, 0),
		chunk::index(0, -1, +1),
		chunk::index(+1, -1, +1)
	},
};

chunk::index		right_occluders_offsets[4][3] =
{
	{
		chunk::index(+1, +1, 0),
		chunk::index(+1, 0, +1),
		chunk::index(+1, +1, +1)
	},

	{
		chunk::index(+1, -1, 0),
		chunk::index(+1, 0, +1),
		chunk::index(+1, -1, +1)
	},

	{
		chunk::index(+1, -1, 0),
		chunk::index(+1, 0, -1),
		chunk::index(+1, -1, -1)
	},

	{
		chunk::index(+1, +1, 0),
		chunk::index(+1, 0, -1),
		chunk::index(+1, +1, -1)
	},
};

chunk::index		left_occluders_offsets[4][3] =
{
	{
		chunk::index(-1, -1, 0),
		chunk::index(-1, 0, -1),
		chunk::index(-1, -1, -1)
	},

	{
		chunk::index(-1, -1, 0),
		chunk::index(-1, 0, +1),
		chunk::index(-1, -1, +1)
	},

	{
		chunk::index(-1, +1, 0),
		chunk::index(-1, 0, +1),
		chunk::index(-1, +1, +1)
	},

	{
		chunk::index(-1, +1, 0),
		chunk::index(-1, 0, -1),
		chunk::index(-1, +1, -1)
	}
};