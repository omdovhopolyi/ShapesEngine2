#include "InputCommandsCollection.h"
#include "Commands/Loaders/InputCommandsLoadersCollection.h"
#include "Commands/Loaders/InputCommandLoader.h"
#include "Utils/Assert.h"

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
        tinyxml2::XMLDocument doc;

        const auto error = doc.LoadFile("../assets/configs/commands.xml");
        if (error != tinyxml2::XML_SUCCESS)
        {
            Assert(error != tinyxml2::XML_SUCCESS, "[InputCommandsCollection::LoadFromXml] Can not read commands.xml");
            return;
        }

        if (auto elements = doc.FirstChildElement("items"))
        {
            auto element = elements->FirstChildElement("item");
            while (element)
            {
                const auto typeAttr = element->FindAttribute("type");
                const auto idAttr = element->FindAttribute("id");

                if (!typeAttr)
                {
                    Assert(!typeAttr, "[InputCommandsCollection::LoadFromXml] No 'type' attribute in command");
                    continue;
                }

                if (!idAttr)
                {
                    Assert(!idAttr, "[InputCommandsCollection::LoadFromXml] No 'id' attribute in command");
                    continue;
                }

                const auto id = idAttr->Value();
                const auto type = typeAttr->Value();

                if (auto loader = InputCommandsLoadersCollection::Instance().GetLoader(type))
                {
                    auto serialization = Serialization(_systems, element);

                    auto command = loader->LoadCommand(serialization);
                    command->SetType(type);
                    _commands[id] = std::move(command);
                }

                element = element->NextSiblingElement();
            }
        }
    }

    void InputCommandsCollection::ClearCommands()
    {
        _commands.clear();
    }
}
