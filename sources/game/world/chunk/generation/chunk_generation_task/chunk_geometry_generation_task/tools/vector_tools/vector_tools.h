#pragma once

namespace			game::vector_tools
{
	template		<typename type>
	static void		append(vector<type> &target, const vector<type> &source)
	{
		target.insert(target.end(), source.begin(), source.end());
	}
}