#include "TimeSystem.h"
#include "Utils/Assert.h"

namespace shen
{
	REGISTER_SYSTEMS_FACTORY(TimeSystem)

	void TimeSystem::Start()
	{
		_lastUpdateTime = std::chrono::high_resolution_clock::now();
	}

	void TimeSystem::Update()
	{
		CalculateDt();
		UpdateGameTime();
	}

	float TimeSystem::Dt() const
	{
		return _dt;
	}

	float TimeSystem::GameDt() const
	{
		return _gameDt;
	}

	void TimeSystem::AppActivated()
	{
		PauseGame(false);
	}

	void TimeSystem::AppDeactivated()
	{
		PauseGame(true);
	}

	void TimeSystem::PauseGame(bool pause)
	{
		if (pause)
		{
			_gamePausedCounter++;
		}
		else
		{
			Assert(_gamePausedCounter > 0, "[TimeSystem::PauseGame]");
			_gamePausedCounter--;
			if (_gamePausedCounter < 0)
			{
				_gamePausedCounter = 0;
			}
		}
	}

	bool TimeSystem::IsGamePaused() const
	{
		return _gamePausedCounter > 0;
	}

	void TimeSystem::SetGameTimeScale(float scale)
	{
		_gameTimeScale = scale;
	}

	float TimeSystem::GetGameTimeScale() const
	{
		return _gameTimeScale;
	}

	void TimeSystem::CalculateDt()
	{
		auto now = std::chrono::high_resolution_clock::now();
		_dt = std::chrono::duration_cast<std::chrono::microseconds>(now - _lastUpdateTime).count() / (1000.f * 1000.f);
		_lastUpdateTime = now;
	}

	void TimeSystem::UpdateGameTime()
	{
		_gameDt = IsGamePaused() ? 0.f : (_dt * _gameTimeScale);
	}
}
