module;

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Equinox/Macros.hpp>

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

        inline void setKeyboardButtonCallback(
            void (*callback)(GLFWwindow*, int, int ,int, int)) noexcept;

        inline void run(const std::function<void(void)>& func) noexcept;

        inline void setName(std::string_view name) noexcept;

        inline void close() noexcept;

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

    inline void Window::run(const std::function<void(void)>& func) noexcept
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

        const char* vss =
            "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "}\n\0";
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vss, NULL);
        glCompileShader(vertexShader);
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout << "VS CE: " << infoLog << '\n';
        }

        const char* fss =
            "#version 330 core\n"
            "out vec4 FragColor;\n"
            "void main()\n"
            "{\n"
            "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
            "}\n\0";
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fss, NULL);
        glCompileShader(fragmentShader);
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cout << "FS CE: " << infoLog << '\n';
        }

        unsigned int shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cout << "Shader Link Error: " << infoLog << '\n';
        }
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        float vertices[] = {
            0.5f, 0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f
        };
        unsigned int indices[] = {
            0, 1, 3,
            1, 2, 3
        };

        unsigned int VBO, VAO, EBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);

        while (!glfwWindowShouldClose(m_Window))
        {
            std::invoke(func);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glUseProgram(shaderProgram);
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            glfwSwapBuffers(m_Window);
            glfwPollEvents();
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
