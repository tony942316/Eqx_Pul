module;

#include <glad/glad.h>
#include <Equinox/Macros.hpp>

export module Eqx.GlfwMod.Shader;

import Equinox;

export namespace glfwm
{
    class Shader
    {
    public:
        explicit inline Shader(std::string_view vs,
            std::string_view fs) noexcept;
        inline Shader(Shader&& other) noexcept;
        inline Shader& operator= (Shader&& other) noexcept;
        inline ~Shader() noexcept;

        Shader(const Shader&) = delete;
        Shader& operator= (const Shader&) = delete;

        inline void enable() const noexcept;
        inline void disable() const noexcept;

        inline void setInt(std::string_view name, int value) const noexcept;
        inline void setFloat(std::string_view name, float value) const noexcept;

        static inline Shader parse(std::string_view vsPath,
                std::string_view fsPath) noexcept;

    private:
        unsigned int m_Shader;
    };
}

namespace glfwm
{
    inline Shader::Shader(std::string_view vs, std::string_view fs) noexcept
        :
        m_Shader(glCreateProgram())
    {
        eqx::ENSURE_HARD(m_Shader != 0,
            "Failed To Create Shader Program!!!"sv);

        const char* vSource = vs.data();
        const char* fSource = fs.data();
        unsigned int vShader = glCreateShader(GL_VERTEX_SHADER);
        unsigned int fShader = glCreateShader(GL_FRAGMENT_SHADER);
        int success;
        char infoLog[512];

        glShaderSource(vShader, 1, &vSource, nullptr);
        glShaderSource(fShader, 1, &fSource, nullptr);

        glCompileShader(vShader);
        glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vShader, 512, nullptr, infoLog);
            eqx::ENSURE_HARD(success, infoLog);
        }

        glCompileShader(fShader);
        glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fShader, 512, nullptr, infoLog);
            eqx::ENSURE_HARD(success, infoLog);
        }

        glAttachShader(m_Shader, vShader);
        glAttachShader(m_Shader, fShader);

        glLinkProgram(m_Shader);
        glGetProgramiv(m_Shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(m_Shader, 512, nullptr, infoLog);
            eqx::ENSURE_HARD(success, infoLog);
        }

        glDeleteShader(vShader);
        glDeleteShader(fShader);
    }

    inline Shader::Shader(Shader&& other) noexcept
        :
        m_Shader(std::move(other.m_Shader))
    {
        other.m_Shader = 0;
    }

    inline Shader& Shader::operator= (Shader&& other) noexcept
    {
        std::swap(m_Shader, other.m_Shader);
        return *this;
    }

    inline Shader::~Shader() noexcept
    {
        if (m_Shader != 0)
        {
            glDeleteProgram(m_Shader);
        }
    }

    inline void Shader::enable() const noexcept
    {
        glUseProgram(m_Shader);
    }

    inline void Shader::disable() const noexcept
    {
        glUseProgram(0U);
    }

    inline void Shader::setInt(std::string_view name, int value) const noexcept
    {
        enable();
        glUniform1i(glGetUniformLocation(m_Shader, name.data()), value);
        disable();
    }

    inline void Shader::setFloat(std::string_view name,
        float value) const noexcept
    {
        enable();
        glUniform1f(glGetUniformLocation(m_Shader, name.data()), value);
        disable();
    }

    inline Shader Shader::parse(std::string_view vsPath,
        std::string_view fsPath) noexcept
    {
        eqx::ENSURE_HARD(std::filesystem::exists(vsPath),
            "Vertex Shader Doesn't Exist!!!"sv);
        eqx::ENSURE_HARD(std::filesystem::exists(fsPath),
            "Fragment Shader Doesn't Exist!!!"sv);

        auto vsFile = std::ifstream{vsPath.data(), std::ios::in};
        auto fsFile = std::ifstream{fsPath.data(), std::ios::in};

        auto vsSource = (std::stringstream{} << vsFile.rdbuf()).str();
        auto fsSource = (std::stringstream{} << fsFile.rdbuf()).str();

        return Shader{vsSource, fsSource};
    }
}
