#pragma once

#include <string>

namespace shen
{
    class SystemsManager;
    class StateMachineSystem;

    class State
    {
    public:
        State();
        State(const std::string& id);
        State(const State& state);
        State(State&& state);
        virtual ~State();

        virtual void Init(StateMachineSystem* stateMachineSystem);
        virtual void OnEnter(const std::string& fromState);
        virtual void Update();
        virtual void OnExit(const std::string& toState);

        void SetId(const std::string& stateId);
        const std::string& GetId() const;

        void SetOwner(StateMachineSystem* owner);
        SystemsManager* GetSystemsManager() const;

    protected:
        StateMachineSystem* _stateMachineSystem = nullptr;
        std::string _id;
    };
}
