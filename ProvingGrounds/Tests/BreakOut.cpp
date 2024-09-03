export module Eqx.Pul.Tests.BreakOut;

import <Eqx/std.hpp>;

import <Eqx/TPL/glm/glm.hpp>;

import Eqx.Lib;
import Eqx.Pul;

namespace tests::breakout
{
    constinit auto m_Shader = std::optional<eqx::Shader>{};

    struct player
    {
        eqx::CQuad quad;
        float dir;
        float speed;
    };

    struct brick
    {
        eqx::CQuad quad;
    };

    struct ball
    {
        eqx::CQuad quad;
        eqx::Point<float> dir;
        float speed;
    };

    constinit auto m_Player = player{};
    constinit auto m_Ball = ball{};
    constinit auto m_Bricks = std::array<brick, 55_uz>{};

    export inline void run(const eqx::Window& window) noexcept;
    export inline void init(const eqx::Window& window) noexcept;
    export inline void term() noexcept;
}

namespace tests::breakout
{
    inline void run(const eqx::Window& window) noexcept
    {
        eqx::renderer::draw(m_Shader.value(), m_Player.quad);
        eqx::renderer::draw(m_Shader.value(), m_Ball.quad);
        std::ranges::for_each(m_Bricks, [](const brick& b)
            {
                eqx::renderer::draw(m_Shader.value(), b.quad);
            });

        if (eqx::keyboard::isReleased(eqx::keyboard::Key::D)
            && eqx::keyboard::isReleased(eqx::keyboard::Key::A))
        {
            m_Player.dir = 0.0f;
        }
        else if (eqx::keyboard::isPressed(eqx::keyboard::Key::D)
            && eqx::keyboard::isPressed(eqx::keyboard::Key::A))
        {
            m_Player.dir = 0.0f;
        }
        else if (eqx::keyboard::isPressed(eqx::keyboard::Key::D))
        {
            m_Player.dir = 1.0f;
        }
        else if (eqx::keyboard::isPressed(eqx::keyboard::Key::A))
        {
            m_Player.dir = -1.0f;
        }

        if (eqx::equals(m_Ball.dir, eqx::Point<float>{0.0f, 0.0f}))
        {
            m_Ball.quad.setPos(m_Player.quad.getPos() + eqx::Point<float>{45.0f, 15.0f});
        }

        if (eqx::keyboard::isPressed(eqx::keyboard::Key::Space)
            && eqx::equals(m_Ball.dir, eqx::Point<float>{0.0f, 0.0f}))
        {
            m_Ball.dir = eqx::Point<float>{0.0f, 1.0f};
        }

        if (eqx::keyboard::isPressed(eqx::keyboard::Key::R))
        {
            m_Ball.dir = eqx::Point<float>{0.0f, 0.0f};
            m_Ball.quad.setPos(m_Player.quad.getPos() + eqx::Point<float>{45.0f, 15.0f});
            for (auto i = 0_uz; i < std::ranges::size(m_Bricks); ++i)
            {
                m_Bricks.at(i).quad.setRect(eqx::Rectangle<float>{
                    10.0f + (60.0f * i) - (60.0f * 11.0f * eqx::floor(i / 11.0f)),
                    -10.0f - (15.0f * eqx::floor(i / 11.0f)),
                    50.0f, 10.0f});
                m_Bricks.at(i).quad.setZ(10.0f);
                m_Bricks.at(i).quad.setColor(eqx::CQuad::Color{255_u8, 0_u8, 0_u8});
                m_Ball.speed = 175.0f;
            }
        }

        if (m_Player.quad.getPos().x < 0.0f)
        {
            m_Player.quad.setPos(eqx::Point<float>{0.0f, m_Player.quad.getPos().y});
        }
        else if (m_Player.quad.getRect().getTopRightPoint().x > window.getWidth())
        {
            m_Player.quad.setPos(eqx::Point<float>{window.getWidth() - m_Player.quad.getRect().w, m_Player.quad.getPos().y});
        }

        if (eqx::intersect(m_Ball.quad.getRect(), m_Player.quad.getRect()))
        {
            auto dx = m_Ball.quad.getPos().x - m_Player.quad.getRect().getCenterPoint().x;
            auto dis = dx / (m_Player.quad.getRect().w / 2.0f);
            m_Ball.dir = eqx::normalize(eqx::Point<float>{dis, m_Ball.dir.y * -1.0f});
            m_Ball.quad.setPos(eqx::Point<float>{m_Ball.quad.getPos().x, m_Ball.quad.getPos().y + 5.0f});
        }

        std::ranges::for_each(m_Bricks, [](brick& b)
            {
                if (eqx::intersect(b.quad.getRect(), m_Ball.quad.getRect()))
                {
                    b.quad.setRect(eqx::Rectangle<float>{0.0f, 0.0f, 0.0f, 0.0f});
                    m_Ball.dir.y = -m_Ball.dir.y;
                    m_Ball.speed += 5.0f;
                }
            });

        if (m_Ball.quad.getPos().x > window.getWidth())
        {
            m_Ball.dir.x = -m_Ball.dir.x;
            m_Ball.quad.setPos(eqx::Point<float>{m_Ball.quad.getPos().x - 5.0f, m_Ball.quad.getPos().y});
        }
        else if (m_Ball.quad.getPos().x < 0.0f)
        {
            m_Ball.dir.x = -m_Ball.dir.x;
            m_Ball.quad.setPos(eqx::Point<float>{m_Ball.quad.getPos().x + 5.0f, m_Ball.quad.getPos().y});
        }

        if (m_Ball.quad.getPos().y > 0.0f)
        {
            m_Ball.dir.y = -m_Ball.dir.y;
            m_Ball.quad.setPos(eqx::Point<float>{m_Ball.quad.getPos().x, m_Ball.quad.getPos().y - 5.0f});
        }

        m_Player.quad.setPos(m_Player.quad.getPos() + eqx::Point<float>{
            (m_Player.dir * m_Player.speed * window.getDeltaTime()), 0.0f});

        m_Ball.quad.setPos(m_Ball.quad.getPos()
            + (m_Ball.dir * m_Ball.speed * window.getDeltaTime()));
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

        m_Player.speed = 300.0f;
        m_Player.dir = 0.0f;
        m_Player.quad.setRect(eqx::Rectangle<float>{290.0f, -375.0f, 100.0f, 20.0f});
        m_Player.quad.setZ(10.0f);
        m_Player.quad.setColor(eqx::CQuad::Color{0_u8, 255_u8, 0_u8});

        m_Ball.speed = 175.0f;
        m_Ball.dir = eqx::Point<float>{0.0f, 0.0f};
        m_Ball.quad.setRect(eqx::Rectangle<float>{335.0f, -360.0f, 10.0f, 10.0f});
        m_Ball.quad.setZ(10.0f);
        m_Ball.quad.setColor(eqx::CQuad::Color{0_u8, 0_u8, 255_u8});

        for (auto i = 0_uz; i < std::ranges::size(m_Bricks); ++i)
        {
            m_Bricks.at(i).quad.setRect(eqx::Rectangle<float>{
                10.0f + (60.0f * i) - (60.0f * 11.0f * eqx::floor(i / 11.0f)),
                -10.0f - (15.0f * eqx::floor(i / 11.0f)),
                50.0f, 10.0f});
            m_Bricks.at(i).quad.setZ(10.0f);
            m_Bricks.at(i).quad.setColor(eqx::CQuad::Color{255_u8, 0_u8, 0_u8});
        }
    }

    inline void term() noexcept
    {
        m_Shader.reset();
    }
}
