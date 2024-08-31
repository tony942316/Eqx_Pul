export module GlfwMod.Tests;

import <Eqx/std.hpp>;

import Eqx.Lib;
import Eqx.GlfwMod;

import GlfwMod.Tests.Basic;
import GlfwMod.Tests.Texture;
import GlfwMod.Tests.MVP;
import GlfwMod.Tests.CQuad;
import GlfwMod.Tests.TxQuad;
import GlfwMod.Tests.BreakOut;

namespace glfwmod::tests
{
    enum class State : char
    {
        Basic,
        Texture,
        MVP,
        CQuad,
        TxQuad,
        BreakOut,
        None
    };

    constinit auto m_State = State::None;
    constinit auto m_Window = std::optional<glfwm::Window>{};

    export inline void run() noexcept;
}

namespace glfwmod::tests
{
    inline void run() noexcept
    {
        glfwm::Window::init();

        m_Window.emplace(680, 400, "Glfwm Proving Grounds"sv);
        m_Window->makeCurrent();

        glfwmod::tests::basic::init();
        glfwmod::tests::texture::init();
        glfwmod::tests::mvp::init(m_Window.value());
        glfwmod::tests::cquad::init(m_Window.value());
        glfwmod::tests::txquad::init(m_Window.value());
        glfwmod::tests::breakout::init(m_Window.value());

        m_Window->run([]()
        {
            m_Window->setName("Glfwm Proving Grounds"sv);

            if (glfwm::keyboard::isPressed(glfwm::keyboard::Key::N0))
            {
                m_State = State::None;
            }
            else if (glfwm::keyboard::isPressed(glfwm::keyboard::Key::N1))
            {
                m_State = State::Basic;
            }
            else if (glfwm::keyboard::isPressed(glfwm::keyboard::Key::N2))
            {
                m_State = State::Texture;
            }
            else if (glfwm::keyboard::isPressed(glfwm::keyboard::Key::N3))
            {
                m_State = State::MVP;
            }
            else if (glfwm::keyboard::isPressed(glfwm::keyboard::Key::N4))
            {
                m_State = State::CQuad;
            }
            else if (glfwm::keyboard::isPressed(glfwm::keyboard::Key::N5))
            {
                m_State = State::TxQuad;
            }
            else if (glfwm::keyboard::isPressed(glfwm::keyboard::Key::N6))
            {
                m_State = State::BreakOut;
            }
            else if (glfwm::keyboard::isPressed(glfwm::keyboard::Key::Escape))
            {
                m_Window->close();
            }

            switch (m_State)
            {
            case State::None:
                break;
            case State::Basic:
                glfwmod::tests::basic::run(m_Window.value());
                break;
            case State::Texture:
                glfwmod::tests::texture::run();
                break;
            case State::MVP:
                glfwmod::tests::mvp::run();
                break;
            case State::CQuad:
                glfwmod::tests::cquad::run(m_Window.value());
                break;
            case State::TxQuad:
                glfwmod::tests::txquad::run();
                break;
            case State::BreakOut:
                glfwmod::tests::breakout::run(m_Window.value());
                break;
            default:
                break;
            }
        });

        glfwmod::tests::basic::term();
        glfwmod::tests::texture::term();
        glfwmod::tests::mvp::term();
        glfwmod::tests::cquad::term();
        glfwmod::tests::txquad::term();
        glfwmod::tests::breakout::term();
        m_Window.reset();
        glfwm::Window::term();
    }
}
