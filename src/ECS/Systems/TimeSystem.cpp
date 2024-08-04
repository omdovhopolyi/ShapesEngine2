#include "TimeSystem.h"

namespace shen
{
	REGISTER_SYSTEMS_FACTORY(TimeSystem)

	void TimeSystem::Start()
	{
		_lastUpdateTime = std::chrono::high_resolution_clock::now();
	}

	void TimeSystem::Update()
	{
		auto now = std::chrono::high_resolution_clock::now();
		_dt = std::chrono::duration_cast<std::chrono::microseconds>(now - _lastUpdateTime).count() / (1000.f * 1000.f);
		_lastUpdateTime = now;
	}

	float TimeSystem::Dt() const
	{
		return _dt;
	}
}
