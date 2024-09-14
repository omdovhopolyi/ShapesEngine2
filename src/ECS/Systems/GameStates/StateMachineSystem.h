#pragma once

#include "ECS/Systems/BaseSystems/UpdateSystem.h"
#include "Utils/Assert.h"
#include <format>
#include <memory>

namespace shen
{
    class State;

    class StateMachineSystem
        : public UpdateSystem
    {
        SYSTEMS_FACTORY(StateMachineSystem)

    public:
        void Start() override;
        void Update() override;
        void ScheduleState(const std::string& stateId);
        State* GetActiveState() const;
        const std::string& GetActiveStateId() const;
        State* GetState(const std::string& stateId) const;

        template<class T>
        void RegisterState(const std::string& stateId);

    private:
        void CheckAndChangeState();

    private:
        State* _activeState;
        std::string _scheduledStateId;
        std::map<std::string, std::unique_ptr<State>> _states;
    };

    template<class T>
    void StateMachineSystem::RegisterState(const std::string& stateId)
    {
        const auto [it, isRegistered] = _states.insert({ stateId, std::make_unique<T>(stateId) });
        Assert(isRegistered, std::format("Can not register state {}", stateId));
    }
}
