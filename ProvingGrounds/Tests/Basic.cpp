export module Eqx.Pul.Tests.Basic;

import <Eqx/std.hpp>;

import Eqx.Lib;
import Eqx.Pul;

namespace tests::basic
{
    constinit auto m_Shader = std::optional<eqx::Shader>{};
    constinit auto m_Vertices = std::optional<eqx::VertexArray>{};

    export inline void run(eqx::Window& window) noexcept;
    export inline void init() noexcept;
    export inline void term() noexcept;
}

namespace tests::basic
{
    inline void run(eqx::Window& window) noexcept
    {
        auto name = std::string{};
        name += eqx::mouse::getPosition().toString();
        name += " : "sv;
        if (eqx::keyboard::isPressed('A'))
        {
            name += " \'A\' Pressed!";
        }
        else
        {
            name += " \'A\' Released!";
        }
        window.setName(name);

        eqx::renderer::draw(m_Shader.value(), m_Vertices.value());
    }

    inline void init() noexcept
    {
        auto vertices = std::array<float, 12>{
            0.5f, 0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f
        };

        auto indices = std::array<unsigned int, 6>{
            0, 1, 3,
            1, 2, 3
        };

        auto attr = std::array<unsigned int, 1>{3};

        m_Vertices.emplace(attr);
        m_Vertices->addVertices(vertices);
        m_Vertices->addIndices(indices);

        m_Shader.emplace(eqx::Shader::parse(
            "Resources/Shaders/Basic/vs.glsl"sv,
            "Resources/Shaders/Basic/fs.glsl"sv));
    }

    inline void term() noexcept
    {
        m_Shader.reset();
        m_Vertices.reset();
    }
}
