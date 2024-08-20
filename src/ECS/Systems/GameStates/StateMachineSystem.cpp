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
        if (_activeState)
        {
            _activeState->Update();
        }
    }

    void StateMachineSystem::ScheduleState(const std::string& stateId)
    {
        _scheduledStateId = stateId;
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
        }
    }
}
