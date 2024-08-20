#include "State.h"
#include "ECS/Systems/GameStates/StateMachineSystem.h"

namespace shen
{
    State::State() = default;
    State::~State() = default;

    void State::Init(StateMachineSystem* stateMachineSystem)
    {
        _stateMachineSystem = stateMachineSystem;
    }

    void State::OnEnter(const std::string& fromState)
    {
        //
    }

    void State::Update()
    {
        //
    }

    void State::OnExit(const std::string& toState)
    {
        //
    }

    void State::SetState(const std::string& stateId)
    {
        _id = stateId;
    }

    const std::string& State::GetId() const
    {
        return _id;
    }
}
