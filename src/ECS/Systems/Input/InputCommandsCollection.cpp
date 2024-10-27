#include "InputCommandsCollection.h"
#include "Commands/Loaders/InputCommandsLoadersCollection.h"
#include "Commands/Loaders/InputCommandLoader.h"
#include "Serialization/Serialization.h"
#include "Utils/Assert.h"
#include "Utils/FilePath.h"

namespace shen
{
    REGISTER_SYSTEMS_FACTORY(InputCommandsCollection)

    void InputCommandsCollection::Start()
    {
        LoadFromXml();
    }

    void InputCommandsCollection::Stop()
    {
        ClearCommands();
    }

    Command* InputCommandsCollection::GetCommandById(const std::string& commandId) const
    {
        if (auto it = _commands.find(commandId); it != _commands.end())
        {
            return it->second.get();
        }

        return nullptr;
    }

    void InputCommandsCollection::LoadFromXml()
    {
        auto serialization = Serialization{ _systems, FilePath::Path("assets/configs/commands.xml").c_str()};
        serialization.SetupElement("items");
        serialization.ForAllChildElements("item", [&](const Serialization& element)
        {
            if (const auto type = element.GetStr("type"); !type.empty())
            {
                if (auto loader = InputCommandsLoadersCollection::Instance().GetLoader(type))
                {
                    auto command = loader->LoadCommand(element);
                    auto id = command->GetId();
                    _commands[id] = std::move(command);
                }
            }
        });
    }

    void InputCommandsCollection::ClearCommands()
    {
        _commands.clear();
    }
}
