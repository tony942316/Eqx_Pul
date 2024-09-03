export module Eqx.Pul.Keyboard;

import <Eqx/std.hpp>;

import <Eqx/TPL/glfw/glfw.hpp>;

import <Eqx/Lib/Macros.hpp>;
import Eqx.Lib;

namespace eqx::keyboard
{
    export
    {
        enum class State : char
        {
            Up = GLFW_RELEASE,
            Down = GLFW_PRESS,
            None
        };

        enum class Key : int
        {
            A = GLFW_KEY_A,
            B = GLFW_KEY_B,
            C = GLFW_KEY_C,
            D = GLFW_KEY_D,
            E = GLFW_KEY_E,
            F = GLFW_KEY_F,
            G = GLFW_KEY_G,
            H = GLFW_KEY_H,
            I = GLFW_KEY_I,
            J = GLFW_KEY_J,
            K = GLFW_KEY_K,
            L = GLFW_KEY_L,
            M = GLFW_KEY_M,
            N = GLFW_KEY_N,
            O = GLFW_KEY_O,
            P = GLFW_KEY_P,
            Q = GLFW_KEY_Q,
            R = GLFW_KEY_R,
            S = GLFW_KEY_S,
            T = GLFW_KEY_T,
            U = GLFW_KEY_U,
            V = GLFW_KEY_V,
            W = GLFW_KEY_W,
            X = GLFW_KEY_X,
            Y = GLFW_KEY_Y,
            Z = GLFW_KEY_Z,
            N0 = GLFW_KEY_0,
            N1 = GLFW_KEY_1,
            N2 = GLFW_KEY_2,
            N3 = GLFW_KEY_3,
            N4 = GLFW_KEY_4,
            N5 = GLFW_KEY_5,
            N6 = GLFW_KEY_6,
            N7 = GLFW_KEY_7,
            N8 = GLFW_KEY_8,
            N9 = GLFW_KEY_9,
            Space = GLFW_KEY_SPACE,
            Escape = GLFW_KEY_ESCAPE,
            Enter = GLFW_KEY_ENTER,
            Tab = GLFW_KEY_TAB,
            Up = GLFW_KEY_UP,
            Down = GLFW_KEY_DOWN,
            Left = GLFW_KEY_LEFT,
            Right = GLFW_KEY_RIGHT
        };

        inline void buttonCallback([[maybe_unused]] GLFWwindow* window, int key,
            [[maybe_unused]] int scancode, int action,
            [[maybe_unused]] int mods) noexcept;

        [[nodiscard]] inline State getKey(Key key) noexcept;
        [[nodiscard]] inline bool isPressed(Key key) noexcept;
        [[nodiscard]] inline bool isPressed(char key) noexcept;
        [[nodiscard]] inline bool isReleased(Key key) noexcept;
        [[nodiscard]] inline bool isReleased(char key) noexcept;
    }

    constinit auto s_Keys =
        std::invoke([]() constexpr
            {
                auto result = std::array<State, 400_uz>{};
                result.fill(State::Up);
                return result;
            });
}

namespace eqx::keyboard
{
    inline void buttonCallback([[maybe_unused]] GLFWwindow* window, int key,
        [[maybe_unused]] int scancode, int action,
        [[maybe_unused]] int mods) noexcept
    {
        if (action == GLFW_REPEAT)
        {
            return;
        }
        s_Keys.at(static_cast<std::size_t>(key)) = static_cast<State>(action);
    }

    [[nodiscard]] inline State getKey(Key key) noexcept
    {
        return s_Keys.at(static_cast<std::size_t>(key));
    }

    [[nodiscard]] inline bool isPressed(Key key) noexcept
    {
        return getKey(key) == State::Down;
    }

    [[nodiscard]] inline bool isPressed(char key) noexcept
    {
        eqx::ENSURE_HARD(key >= 'A' && key <= 'Z',
            "Invalid Char Input!!!"sv);
        return getKey(static_cast<Key>(key)) == State::Down;
    }

    [[nodiscard]] inline bool isReleased(Key key) noexcept
    {
        return getKey(key) == State::Up;
    }

    [[nodiscard]] inline bool isReleased(char key) noexcept
    {
        eqx::ENSURE_HARD(key >= 'A' && key <= 'Z',
            "Invalid Char Input!!!"sv);
        return getKey(static_cast<Key>(key)) == State::Up;
    }
}
