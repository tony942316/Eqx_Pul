export module GlfwMod.Tests.CQuad;

import <Eqx/std.hpp>;

import <Eqx/TPL/glm/glm.hpp>;

import Eqx.Lib;
import Eqx.GlfwMod;

namespace glfwmod::tests::cquad
{
    constinit auto m_Shader = std::optional<glfwm::Shader>{};
    constinit auto m_CQuad = glfwm::CQuad{};

    export inline void run(const glfwm::Window& window) noexcept;
    export inline void init(const glfwm::Window& window) noexcept;
    export inline void term() noexcept;
}

namespace glfwmod::tests::cquad
{
    inline void run(const glfwm::Window& window) noexcept
    {
        glfwm::renderer::draw(m_Shader.value(), m_CQuad);
        m_CQuad.setPos(glfwm::mouse::getPosition());
        auto r = (glfwm::mouse::getPosition().x / static_cast<float>(window.getWidth())) * 255_u8;
        auto g = (-glfwm::mouse::getPosition().y / static_cast<float>(window.getHeight())) * 255_u8;
        m_CQuad.setColor(glfwm::CQuad::Color{
            static_cast<std::uint8_t>(r), static_cast<std::uint8_t>(g), 255_u8});
    }

    inline void init(const glfwm::Window& window) noexcept
    {
        m_Shader.emplace(glfwm::Shader::parse(
            "Resources/Shaders/CQuad/vs.glsl"sv,
            "Resources/Shaders/CQuad/fs.glsl"sv));

        auto proj = glm::ortho(
            0.0f, static_cast<float>(window.getWidth()),
            -1.0f * static_cast<float>(window.getHeight()), 0.0f,
            0.0f, 1000.0f);

        m_Shader->setMat4("u_Projection", proj);

        m_CQuad.setRect(eqx::Rectangle<float>{0.0f, 0.0f, 50.0f, 50.0f});
        m_CQuad.setZ(10.0f);
        m_CQuad.setColor(glfwm::CQuad::Color{255_u8, 255_u8, 255_u8});
    }

    inline void term() noexcept
    {
        m_Shader.reset();
    }
}
