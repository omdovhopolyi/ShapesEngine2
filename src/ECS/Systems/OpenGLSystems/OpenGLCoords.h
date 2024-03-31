#pragma once

namespace shen
{
    // move to database

    static constexpr float vertices[] =
    {
        0.f, 0.f, 0.0f,
        1.f, 0.f, 0.0f,
        1.f, 1.f, 0.0f,
        0.f, 1.f, 0.0f
    };

    static constexpr unsigned int indices[] =
    {
        0, 1, 3,
        1, 2, 3
    };

    static constexpr float gridPlane[] =
    {
        -10.f, -10.f, 0.f,
        10.f, -10.f, 0.f,
        10.f, 10.f, 0.f,
        -10.f, 10.f, 0.f
    };
}
