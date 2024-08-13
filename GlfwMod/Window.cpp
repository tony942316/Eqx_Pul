module;

#include <GLFW/glfw3.h>

export module Eqx.GlfwMod.Window;

import Equinox;

export namespace glfwm
{
    class Window
    {
    public:
        explicit inline Window(int width, int height,
            std::string_view name) noexcept;

        explicit inline Window(Window&& other) noexcept;
        inline Window& operator= (Window&& other) noexcept;

        inline ~Window() noexcept;

        Window(const Window&) = delete;
        Window& operator= (const Window&) = delete;

        inline void setMouseMoveCallback(
            void (*callback)(GLFWwindow*, double, double)) noexcept;

        inline void setMouseButtonCallback(
            void (*callback)(GLFWwindow*, int, int, int)) noexcept;

        inline void run(const std::function<void(void)>& func) noexcept;

        inline void setName(std::string_view name) noexcept;

        static inline void init() noexcept;

        static inline void term() noexcept;

    private:
        GLFWwindow* m_Window;
        int m_Width;
        int m_Height;
        std::string m_Name;
    };
}

namespace glfwm
{
    inline Window::Window(int width, int height, std::string_view name) noexcept
        :
        m_Window(glfwCreateWindow(width, height, "debug", NULL, NULL)),
        m_Width(width),
        m_Height(height),
        m_Name(name)
    {
        setName(name);
    }

    inline Window::Window(Window&& other) noexcept
        :
        m_Window(std::move(other.m_Window)),
        m_Width(std::move(other.m_Width)),
        m_Height(std::move(other.m_Height)),
        m_Name(std::move(other.m_Name))
    {
        m_Window = other.m_Window;
        other.m_Window = nullptr;
    }

    inline Window& Window::operator= (Window&& other) noexcept
    {
        m_Window = std::move(other.m_Window);
        m_Width = std::move(other.m_Width);
        m_Height = std::move(other.m_Height);
        m_Name = std::move(other.m_Name);

        other.m_Window = nullptr;

        return *this;
    }

    inline Window::~Window() noexcept
    {
        if (m_Window != nullptr)
        {
            glfwDestroyWindow(m_Window);
        }
    }

    inline void Window::setMouseMoveCallback(
        void (*callback)(GLFWwindow*, double, double)) noexcept
    {
        glfwSetCursorPosCallback(m_Window, callback);
    }

    inline void Window::setMouseButtonCallback(
        void (*callback)(GLFWwindow*, int, int, int)) noexcept
    {
        glfwSetMouseButtonCallback(m_Window, callback);
    }

    inline void Window::run(const std::function<void(void)>& func) noexcept
    {
        glfwMakeContextCurrent(m_Window);

        while (!glfwWindowShouldClose(m_Window))
        {
            std::invoke(func);

            glfwSwapBuffers(m_Window);
            glfwPollEvents();
        }
    }

    inline void Window::setName(std::string_view name) noexcept
    {
        m_Name = name;
        glfwSetWindowTitle(m_Window, m_Name.c_str());
    }

    inline void Window::init() noexcept
    {
        glfwInit();
    }

    inline void Window::term() noexcept
    {
        glfwTerminate();
    }
}
