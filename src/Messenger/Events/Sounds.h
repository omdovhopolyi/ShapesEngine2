#pragma once

#include "Event.h"
#include <string>

namespace shen
{
    struct PlaySoundEvent : Event
    {
        std::string id;

        PlaySoundEvent(const std::string& soundId)
            : id(soundId)
        {}
    };

    struct PlayMusicEvent : Event
    {
        std::string id;

        PlayMusicEvent(const std::string& trackId)
            : id(trackId)
        {}
    };

    struct StopMusicEvent : Event
    {
        std::string id;

        StopMusicEvent(const std::string& trackId)
            : id(trackId)
        {}
    };
}
