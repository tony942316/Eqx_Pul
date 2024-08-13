module;

#include <GLFW/glfw3.h>

export module Eqx.GlfwMod.Mouse;

import Equinox;

namespace glfwm::mouse
{
    using namespace eqx::literals;

    export
    {
        enum class Button : char
        {
            Left = 0,
            Right = 1,
            None
        };

        enum class State : char
        {
            Up = 0,
            Down = 1,
            None
        };

        inline void moveCallback([[maybe_unused]] GLFWwindow* window,
            double xpos, double ypos) noexcept;

        inline void buttonCallback([[maybe_unused]] GLFWwindow* window,
            int button, int action, [[maybe_unused]] int mods) noexcept;

        [[nodiscard]] inline eqx::Point<float> getPosition(
            Button button = Button::None, State state = State::None) noexcept;

        [[nodiscard]] inline State getState(Button button) noexcept;
    }


    [[nodiscard]] inline eqx::Point<float>& editButtonPosition(
        Button button, State state) noexcept;

    constinit auto m_Position = eqx::Point<float>{};
    constinit auto m_ButtonPosition =
        std::array<eqx::Point<float>, 4_uz>{};
    constinit auto m_ButtonState = std::array<State, 2_uz>{};
}

namespace glfwm::mouse
{
        inline void moveCallback([[maybe_unused]] GLFWwindow* window,
            double xpos, double ypos) noexcept
        {
            m_Position = eqx::Point<float>{static_cast<float>(xpos),
                static_cast<float>(ypos)};
        }

        inline void buttonCallback([[maybe_unused]] GLFWwindow* window,
            int button, int action, [[maybe_unused]] int mods) noexcept
        {
            Button myButton = static_cast<Button>(button);
            State myState = static_cast<State>(action);

            m_ButtonState.at(static_cast<std::size_t>(myButton)) = myState;
            editButtonPosition(myButton, myState) = getPosition();
        }

        [[nodiscard]] inline eqx::Point<float> getPosition(Button button,
            State state) noexcept
        {
            return button == Button::None
                ? m_Position
                : editButtonPosition(button, state);
        }

        [[nodiscard]] inline State getState(
            Button button) noexcept
        {
            return m_ButtonState.at(static_cast<std::size_t>(button));
        }

        [[nodiscard]] inline eqx::Point<float>& editButtonPosition(
            Button button, State state) noexcept
        {
            return m_ButtonPosition.at(static_cast<std::size_t>(
                (2 * static_cast<std::size_t>(button))
                + static_cast<std::size_t>(state)));
        }
}
