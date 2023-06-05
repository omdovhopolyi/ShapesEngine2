#include "Time.h"

// TODO
#include <SDL.h>

namespace shen
{
	void Time::Init()
	{

	}

	void Time::Update()
	{
		int timeToWait = MILLISEC_PER_FRAME - (SDL_GetTicks() - _lastUpdateTime);
		if (timeToWait > 0)
		{
			SDL_Delay(timeToWait);
		}

		_dt = (SDL_GetTicks() - _lastUpdateTime) / 1000.f;
		_lastUpdateTime = SDL_GetTicks();
	}

	float Time::Dt() const
	{
		return _dt;
	}
}
