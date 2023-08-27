#include "Time.h"
#include <chrono>

namespace shen
{
	void Time::Init()
	{
		_lastUpdateTime = std::chrono::high_resolution_clock::now();
	}

	void Time::Update()
	{
		auto now = std::chrono::high_resolution_clock::now();
		_dt = std::chrono::duration_cast<std::chrono::microseconds>(now - _lastUpdateTime).count() / (1000.f * 1000.f);
  		_lastUpdateTime = now;
	}

	float Time::Dt() const
	{
		return _dt;
	}
}
