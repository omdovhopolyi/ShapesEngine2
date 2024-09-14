#include "State.h"
#include "ECS/Systems/GameStates/StateMachineSystem.h"

namespace shen
{
    State::State() = default;
    State::~State() = default;

    State::State(const std::string& id)
        : _id(id)
    {}

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

    void State::SetId(const std::string& stateId)
    {
        _id = stateId;
    }

    const std::string& State::GetId() const
    {
        return _id;
    }
}
