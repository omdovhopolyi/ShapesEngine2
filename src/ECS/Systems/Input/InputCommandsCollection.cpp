#include "InputCommandsCollection.h"
#include "Serialization/LoadersManager.h"
#include "Serialization/WrapperTypes/XmlDataElementWrapper.h"
#include "Utils/Assert.h"
#include "Utils/FilePath.h"
#include "Commands/Command.h"

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

    void InputCommandsCollection::AddCommand(const std::string& id, const std::shared_ptr<Command>& command)
    {
        _commands[id] = command;
    }

    void InputCommandsCollection::LoadFromXml()
    {
        auto elementWrapper = XmlDataElementWrapper{ _systems };
        elementWrapper.LoadFile(FilePath::Path("assets/configs/commands.xml"));
        elementWrapper.ForAllChildren("item", [&](const DataElementWrapper& element)
        {
            if (const auto type = element.GetStr("type"); !type.empty())
            {
                if (auto loader = LoadersManager::Instance().GetLoader(type))
                {
                    auto command = std::dynamic_pointer_cast<Command>(loader->CreateAndLoad(element));
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
