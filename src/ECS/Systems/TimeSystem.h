#pragma once

#include "BaseSystems/UpdateSystem.h"

#include <chrono>

namespace shen
{
    class TimeSystem
        : public UpdateSystem
    {
        SYSTEMS_FACTORY(TimeSystem)

    public:
        void Start();
        void Update();
        float Dt() const;
        int DtMs() const;
        float GameDt() const;
        int GameDtMs() const;

        void AppActivated() override;
        void AppDeactivated() override;

        void PauseGame(bool pause);
        bool IsGamePaused() const;

        void SetGameTimeScale(float scale);
        float GetGameTimeScale() const;

        const std::chrono::steady_clock::time_point& GetLastUpdateTime() { return _lastUpdateTime; }

    private:
        void CalculateDt();
        void UpdateGameTime();

    private:
        float _dt = 0.f;
        float _gameDt = 0.f;
        float _uiDt = 0.f;
        float _gameTimeScale = 1.f;
        int _gameDtMs = 0;
        int _dtMs = 0;
        int _gamePausedCounter = 0;
        std::chrono::steady_clock::time_point _lastUpdateTime;
    };
}
