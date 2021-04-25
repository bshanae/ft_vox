#pragma once

namespace					game
{
	class					light_mixer;
}

class						game::light_mixer
{
public :
							light_mixer() = delete;
							~light_mixer() = delete;

	static float 			mix_light_and_ao(float light_level, float ao_level)
	{
		return light_level - ao_level * light_level * ao_weight;
	}

private :

	static constexpr float	ao_weight = 0.4f;
};