export module GlfwMod.Tests.CQuad;

import <Eqx/std.hpp>;

import Eqx.Lib;
import Eqx.GlfwMod;

namespace glfwmod::tests::cquad
{
    constinit auto m_Shader = std::optional<glfwm::Shader>{};
    constinit auto m_CQuad = glfwm::CQuad{};

    export inline void run() noexcept;
    export inline void init(const glfwm::Window& window) noexcept;
    export inline void term() noexcept;
}

namespace glfwmod::tests::cquad
{
    inline void run() noexcept
    {
        glfwm::renderer::draw(m_Shader.value(), m_CQuad);
    }

    inline void init(const glfwm::Window& window) noexcept
    {
        m_Shader.emplace(glfwm::Shader::parse(
            "Resources/Shaders/CQuad/vs.glsl"sv,
            "Resources/Shaders/CQuad/fs.glsl"sv));

        window.setOrtho("u_Projection"sv, m_Shader.value());

        m_CQuad.setRect(eqx::Rectangle<float>{100.0f, 100.0f, 50.0f, 50.0f});
        m_CQuad.setZ(10.0f);
        m_CQuad.setColor(glfwm::CQuad::Color{255_u8, 25_u8, 25_u8});
    }

    inline void term() noexcept
    {
        m_Shader.reset();
    }
}
