#pragma once

#include "epsilon.h"

vector<GLfloat>		front_vertices =
{
	+0.5f, +0.5f, +0.5f,
	-0.5f, +0.5f, +0.5f,
	-0.5f, -0.5f, +0.5f,
	+0.5f, -0.5f, +0.5f
};

vector<GLfloat>		back_vertices =
{
	+0.5f, +0.5f, -0.5f,
	+0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, +0.5f, -0.5f
};

vector<GLfloat>		top_vertices =
{
	-0.5f, +0.5f, +0.5f,
	+0.5f, +0.5f, +0.5f,
	+0.5f, +0.5f, -0.5f,
	-0.5f, +0.5f, -0.5f
};

vector<GLfloat>		bottom_vertices =
{
	-0.5f, -0.5f, +0.5f,
	-0.5f, -0.5f, -0.5f,
	+0.5f, -0.5f, -0.5f,
	+0.5f, -0.5f, +0.5f
};

vector<GLfloat>		right_vertices =
{
	+0.5f, +0.5f, +0.5f,
	+0.5f, -0.5f, +0.5f,
	+0.5f, -0.5f, -0.5f,
	+0.5f, +0.5f, -0.5f
};

vector<GLfloat>		left_vertices =
{
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, +0.5f,
	-0.5f, +0.5f, +0.5f,
	-0.5f, +0.5f, -0.5f,
};

vector<GLfloat>		first_diagonal_vertices =
{
	+0.5f, +0.5f, +0.5f,
	-0.5f, +0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	+0.5f, -0.5f, +0.5f,
};

vector<GLfloat>		second_diagonal_vertices =
{
	+0.5f, +0.5f, -0.5f,
	-0.5f, +0.5f, +0.5f,
	-0.5f, -0.5f, +0.5f,
	+0.5f, -0.5f, -0.5f,
};