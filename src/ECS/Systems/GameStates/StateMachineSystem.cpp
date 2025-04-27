#include "StateMachineSystem.h"
#include "ECS/Systems/GameStates/State.h"

namespace shen
{
    REGISTER_SYSTEMS_FACTORY(StateMachineSystem)

    void StateMachineSystem::Start()
    {
        for (auto& [id, state] : _states)
        {
            state->Init(this);
        }
    }

    void StateMachineSystem::Update()
    {
        CheckAndChangeState();

        if (_activeState)
        {
            _activeState->Update();
        }
    }

    void StateMachineSystem::AppActivated()
    {
        if (_activeState)
        {
            _activeState->AppActivated();
        }
    }

    void StateMachineSystem::AppDeactivated()
    {
        if (_activeState)
        {
            _activeState->AppDeactivated();
        }
    }

    State* StateMachineSystem::GetActiveState() const
    {
        return _activeState;
    }

    const std::string& StateMachineSystem::GetActiveStateId() const
    {
        if (_activeState)
        {
            return _activeState->GetId();
        }

        static std::string empty;
        return empty;
    }

    State* StateMachineSystem::GetState(const std::string& stateId) const
    {
        if (auto it = _states.find(stateId); it != _states.end())
        {
            return it->second.get();
        }
        return nullptr;
    }

    bool StateMachineSystem::ScheduleState(const std::string& stateId)
    {
        const bool isNewState = (_scheduledStateId != stateId);
        _scheduledStateId = stateId;
        return isNewState;
    }

    const std::string& StateMachineSystem::GetScheduledState() const
    {
        return _scheduledStateId;
    }

    bool StateMachineSystem::IsAnyStateScheduled() const
    {
        return !_scheduledStateId.empty();
    }

    bool StateMachineSystem::IsStateScheduled(const std::string& stateId) const
    {
        return _scheduledStateId == stateId;
    }

    void StateMachineSystem::CheckAndChangeState()
    {
        if (!_scheduledStateId.empty())
        {
            std::string fromStateId;

            if (_activeState)
            {
                fromStateId = _activeState->GetId();
                _activeState->OnExit(_scheduledStateId);
            }

            if (auto nextState = GetState(_scheduledStateId))
            {
                nextState->OnEnter(fromStateId);
                _activeState = std::move(nextState);
            }

            _scheduledStateId.clear();
        }
    }
}
