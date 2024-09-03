export module Eqx.Pul.Window;

import <Eqx/std.hpp>;

import <Eqx/TPL/glad/glad.hpp>;
import <Eqx/TPL/glfw/glfw.hpp>;
import <Eqx/TPL/glm/glm.hpp>;

import <Eqx/Lib/Macros.hpp>;
import Eqx.Lib;

import Eqx.Pul.Mouse;
import Eqx.Pul.Keyboard;
import Eqx.Pul.Shader;

export namespace eqx
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

        inline void setKeyboardButtonCallback(
            void (*callback)(GLFWwindow*, int, int ,int, int)) noexcept;

        inline void makeCurrent() noexcept;

        template <typename T>
            requires requires(const T& f) { std::invoke(f); }
        inline void run(const T& func) noexcept;

        inline void setName(std::string_view name) noexcept;

        inline void close() noexcept;

        inline void setOrtho(std::string_view name,
            const Shader& shader) const noexcept;

        [[nodiscard]] inline int getWidth() const noexcept;

        [[nodiscard]] inline int getHeight() const noexcept;

        [[nodiscard]] inline float getDeltaTime() const noexcept;

        static inline void init() noexcept;

        static inline void term() noexcept;

    private:
        GLFWwindow* m_Window;
        int m_Width;
        int m_Height;
        float m_DT;
        std::string m_Name;
    };
}

namespace eqx
{
    inline Window::Window(int width, int height, std::string_view name) noexcept
        :
        m_Window(glfwCreateWindow(width, height, "debug", NULL, NULL)),
        m_Width(width),
        m_Height(height),
        m_Name(name)
    {
        eqx::ENSURE_HARD(m_Window != nullptr,
            "Glfw Window Creation Failure!!!"sv);
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

    inline void Window::setKeyboardButtonCallback(
        void (*callback)(GLFWwindow*, int, int ,int, int)) noexcept
    {
        glfwSetKeyCallback(m_Window, callback);
    }

    inline void Window::makeCurrent() noexcept
    {
        glfwMakeContextCurrent(m_Window);
        glfwSwapInterval(1);

        eqx::ENSURE_HARD(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress),
            "Failed To Init GLAD!!!"sv);
        glViewport(0, 0, m_Width, m_Height);
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        std::cout << "Version: "sv << glGetString(GL_VERSION) << '\n';
        std::cout << "Max Textures: "sv
            << GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS << '\n';

        setMouseMoveCallback(eqx::mouse::moveCallback);
        setMouseButtonCallback(eqx::mouse::buttonCallback);
        setKeyboardButtonCallback(eqx::keyboard::buttonCallback);
    }

    template <typename T>
        requires requires(const T& f) { std::invoke(f); }
    inline void Window::run(const T& func) noexcept
    {
        auto timer = eqx::StopWatch{};

        std::cout << "Error Num: " << glGetError() << '\n';

        while (!glfwWindowShouldClose(m_Window))
        {
            timer.start();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            std::invoke(func);

            glfwSwapBuffers(m_Window);
            glfwPollEvents();
            timer.stop();
            m_DT = static_cast<float>(timer.getSeconds());
        }
    }

    inline void Window::setName(std::string_view name) noexcept
    {
        m_Name = name;
        glfwSetWindowTitle(m_Window, m_Name.c_str());
    }

    inline void Window::close() noexcept
    {
        glfwSetWindowShouldClose(m_Window, GLFW_TRUE);
    }

    inline void Window::setOrtho(std::string_view name,
        const Shader& shader) const noexcept
    {
        shader.setMat4(name, glm::ortho(
            0.0f, static_cast<float>(m_Width),
            0.0f, static_cast<float>(m_Height),
            -1.0f, 100.0f));
    }

    [[nodiscard]] inline int Window::getWidth() const noexcept
    {
        return m_Width;
    }

    [[nodiscard]] inline int Window::getHeight() const noexcept
    {
        return m_Height;
    }

    [[nodiscard]] inline float Window::getDeltaTime() const noexcept
    {
        return m_DT;
    }

    inline void Window::init() noexcept
    {
        eqx::ENSURE_HARD(glfwInit() == GLFW_TRUE,
            "Glfw Init Failure!!!"sv);
        glfwSetErrorCallback([](int error, const char* desc)
            {
                std::cerr << "Glfw Error: #" << error << " -> " << desc << '\n';
            });
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, false);
    }

    inline void Window::term() noexcept
    {
        glfwTerminate();
    }
}
