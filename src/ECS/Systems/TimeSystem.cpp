#include "TimeSystem.h"
#include "Utils/Assert.h"
#include "Logger/Logger.h"

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

	int TimeSystem::DtMs() const
	{
		return _dtMs;
	}

	float TimeSystem::GameDt() const
	{
		return _gameDt;
	}

	int TimeSystem::GameDtMs() const
	{
		return _gameDtMs;
	}

	void TimeSystem::AppActivated()
	{
		//PauseGame(false);
	}

	void TimeSystem::AppDeactivated()
	{
		//PauseGame(true);
	}

	void TimeSystem::PauseGame(bool pause)
	{
		std::string msg = "[TimeSystem::PauseGame] " + std::to_string(pause);
		Logger::Log(msg);

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
		_dtMs = std::chrono::duration_cast<std::chrono::milliseconds>(now - _lastUpdateTime).count();
		_dt = _dtMs / 1000.f;
		_lastUpdateTime = now;
	}

	void TimeSystem::UpdateGameTime()
	{
		_gameDtMs = IsGamePaused() ? 0 : static_cast<int>(_dtMs * _gameTimeScale);
		_gameDt = _gameDtMs / 1000.f;
		//_gameDt = IsGamePaused() ? 0.f : (_dt * _gameTimeScale);
	}
}
