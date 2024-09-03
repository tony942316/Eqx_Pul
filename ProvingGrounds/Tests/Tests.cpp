export module Eqx.Pul.Tests;

import <Eqx/std.hpp>;

import Eqx.Lib;
import Eqx.Pul;

import Eqx.Pul.Tests.Basic;
import Eqx.Pul.Tests.Texture;
import Eqx.Pul.Tests.MVP;
import Eqx.Pul.Tests.CQuad;
import Eqx.Pul.Tests.TxQuad;
import Eqx.Pul.Tests.BreakOut;

namespace tests
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
    constinit auto m_Window = std::optional<eqx::Window>{};

    export inline void run() noexcept;
}

namespace tests
{
    inline void run() noexcept
    {
        eqx::Window::init();

        m_Window.emplace(680, 400, "Glfwm Proving Grounds"sv);
        m_Window->makeCurrent();

        tests::basic::init();
        tests::texture::init();
        tests::mvp::init(m_Window.value());
        tests::cquad::init(m_Window.value());
        tests::txquad::init(m_Window.value());
        tests::breakout::init(m_Window.value());

        m_Window->run([]()
        {
            m_Window->setName("Glfwm Proving Grounds"sv);

            if (eqx::keyboard::isPressed(eqx::keyboard::Key::N0))
            {
                m_State = State::None;
            }
            else if (eqx::keyboard::isPressed(eqx::keyboard::Key::N1))
            {
                m_State = State::Basic;
            }
            else if (eqx::keyboard::isPressed(eqx::keyboard::Key::N2))
            {
                m_State = State::Texture;
            }
            else if (eqx::keyboard::isPressed(eqx::keyboard::Key::N3))
            {
                m_State = State::MVP;
            }
            else if (eqx::keyboard::isPressed(eqx::keyboard::Key::N4))
            {
                m_State = State::CQuad;
            }
            else if (eqx::keyboard::isPressed(eqx::keyboard::Key::N5))
            {
                m_State = State::TxQuad;
            }
            else if (eqx::keyboard::isPressed(eqx::keyboard::Key::N6))
            {
                m_State = State::BreakOut;
            }
            else if (eqx::keyboard::isPressed(eqx::keyboard::Key::Escape))
            {
                m_Window->close();
            }

            switch (m_State)
            {
            case State::None:
                break;
            case State::Basic:
                tests::basic::run(m_Window.value());
                break;
            case State::Texture:
                tests::texture::run();
                break;
            case State::MVP:
                tests::mvp::run();
                break;
            case State::CQuad:
                tests::cquad::run(m_Window.value());
                break;
            case State::TxQuad:
                tests::txquad::run();
                break;
            case State::BreakOut:
                tests::breakout::run(m_Window.value());
                break;
            default:
                break;
            }
        });

        tests::basic::term();
        tests::texture::term();
        tests::mvp::term();
        tests::cquad::term();
        tests::txquad::term();
        tests::breakout::term();
        m_Window.reset();
        eqx::Window::term();
    }
}
