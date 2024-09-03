export module Eqx.Pul.Tests.CQuad;

import <Eqx/std.hpp>;

import <Eqx/TPL/glm/glm.hpp>;

import Eqx.Lib;
import Eqx.Pul;

namespace tests::cquad
{
    constinit auto m_Shader = std::optional<eqx::Shader>{};
    constinit auto m_CQuad = eqx::CQuad{};

    export inline void run(const eqx::Window& window) noexcept;
    export inline void init(const eqx::Window& window) noexcept;
    export inline void term() noexcept;
}

namespace tests::cquad
{
    inline void run(const eqx::Window& window) noexcept
    {
        eqx::renderer::draw(m_Shader.value(), m_CQuad);
        m_CQuad.setPos(eqx::mouse::getPosition());
        auto r = (eqx::mouse::getPosition().x / static_cast<float>(window.getWidth())) * 255_u8;
        auto g = (-eqx::mouse::getPosition().y / static_cast<float>(window.getHeight())) * 255_u8;
        m_CQuad.setColor(eqx::CQuad::Color{
            static_cast<std::uint8_t>(r), static_cast<std::uint8_t>(g), 255_u8});
    }

    inline void init(const eqx::Window& window) noexcept
    {
        m_Shader.emplace(eqx::Shader::parse(
            "Resources/Shaders/CQuad/vs.glsl"sv,
            "Resources/Shaders/CQuad/fs.glsl"sv));

        auto proj = glm::ortho(
            0.0f, static_cast<float>(window.getWidth()),
            -1.0f * static_cast<float>(window.getHeight()), 0.0f,
            0.0f, 1000.0f);

        m_Shader->setMat4("u_Projection", proj);

        m_CQuad.setRect(eqx::Rectangle<float>{0.0f, 0.0f, 50.0f, 50.0f});
        m_CQuad.setZ(10.0f);
        m_CQuad.setColor(eqx::CQuad::Color{255_u8, 255_u8, 255_u8});
    }

    inline void term() noexcept
    {
        m_Shader.reset();
    }
}
