#pragma once

#include <string>

namespace shen
{
    class StateMachineSystem;

    class State
    {
    public:
        State();
        State(const std::string& id);
        ~State();

        virtual void Init(StateMachineSystem* stateMachineSystem);
        virtual void OnEnter(const std::string& fromState);
        virtual void Update();
        virtual void OnExit(const std::string& toState);

        void SetId(const std::string& stateId);
        const std::string& GetId() const;

    private:
        StateMachineSystem* _stateMachineSystem = nullptr;
        std::string _id;
    };
}
