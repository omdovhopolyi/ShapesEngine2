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
		PauseGame(true);
	}

	void TimeSystem::AppDeactivated()
	{
		PauseGame(false);
	}

	void TimeSystem::PauseGame(bool pause)
	{
		_gamePaused = pause;
	}

	bool TimeSystem::IsGamePaused() const
	{
		return _gamePaused;
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
		_gameDt = _gamePaused ? 0.f : (_dt * _gameTimeScale);
	}
}
