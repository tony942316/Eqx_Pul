export module GlfwMod.Tests;

import Equinox;
import Eqx.GlfwMod;

import GlfwMod.Tests.Basic;

namespace glfwmod::tests
{
    enum class State : char
    {
        Basic,
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

        m_Window.emplace(640, 480, "Glfwm Proving Grounds"sv);
        m_Window->makeCurrent();

        glfwmod::tests::basic::init();

        m_Window->run([]()
        {
            if (glfwm::keyboard::isPressed(glfwm::keyboard::Key::N0))
            {
                m_State = State::None;
            }
            else if (glfwm::keyboard::isPressed(glfwm::keyboard::Key::N1))
            {
                m_State = State::Basic;
            }
            else if (glfwm::keyboard::isPressed(glfwm::keyboard::Key::Escape))
            {
                m_Window->close();
            }

            switch (m_State)
            {
            case State::None:
                m_Window->setName("Glfwm Proving Grounds"sv);
                break;
            case State::Basic:
                glfwmod::tests::basic::run(m_Window.value());
                break;
            default:
                break;
            }
        });

        glfwmod::tests::basic::term();
        m_Window.reset();
        glfwm::Window::term();
    }


}
