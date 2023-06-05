#pragma once

#include "Utils/Singleton.h"
#include "Systems/System.h"

#include <memory>
#include <vector>
#include <map>
#include <typeinfo>
#include <typeindex>

namespace shen
{
    class SystemsManager
        : public Singleton<SystemsManager>
    {
    public:
        void Init();

        template <class T>
        void RegisteSystem()
        {
            _systems.push_back(std::make_unique<T>());
            _mappedSystems[std::type_index(typeid(T))] = _systems.back().get();
        }

        template <class T>
        T* GetSystem() const
        {
            const auto typeIndex = std::type_index(typeid(T));
            auto it = _mappedSystems.find(typeIndex);
            if (it != _mappedSystems.end())
            {
                return it->second.get();
            }
            return nullptr;
        }

        void Start();
        void Update();
        void Stop();
        void Clear();

    private:
        std::vector<std::unique_ptr<System>> _systems;
        std::map<std::type_index, System*> _mappedSystems;
    };

}
