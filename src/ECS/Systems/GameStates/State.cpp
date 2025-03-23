#include "State.h"
#include "ECS/Systems/GameStates/StateMachineSystem.h"

namespace shen
{
    State::State() = default;
    State::State(const State& state) = default;
    State::State(State&& state) = default;
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
        // empty
    }

    void State::Update()
    {
        // emtpy
    }

    void State::OnExit(const std::string& toState)
    {
        // emtpy
    }

    void State::AppActivated()
    {
        // emtpy
    }

    void State::AppDeactivated()
    {
        // emtpy
    }

    void State::SetId(const std::string& stateId)
    {
        _id = stateId;
    }

    const std::string& State::GetId() const
    {
        return _id;
    }

    bool State::ScheduleState(const std::string& stateId)
    {
        if (_stateMachineSystem)
        {
            return _stateMachineSystem->ScheduleState(stateId);
        }

        return false;
    }

    void State::SetOwner(StateMachineSystem* owner)
    {
        _stateMachineSystem = owner;
    }

    SystemsManager* State::GetSystemsManager() const
    {
        if (_stateMachineSystem)
        {
            return _stateMachineSystem->GetSystems();
        }

        return nullptr;
    }
}
