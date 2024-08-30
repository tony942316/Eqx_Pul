export module GlfwMod.Tests.MVP;

import <Eqx/std.hpp>;

import <Eqx/TPL/glm/glm.hpp>;

import Eqx.Lib;

import Eqx.GlfwMod;

namespace glfwmod::tests::mvp
{
    constinit auto m_Shader = std::optional<glfwm::Shader>{};
    constinit auto m_Vertices = std::optional<glfwm::VertexArray>{};
    constinit auto m_Model = glm::mat4(1.0f);

    export inline void run() noexcept;
    export inline void init(const glfwm::Window& window) noexcept;
    export inline void term() noexcept;
}

namespace glfwmod::tests::mvp
{
    inline void run() noexcept
    {
        glfwm::renderer::draw(m_Shader.value(), m_Vertices.value());
        m_Model = glm::rotate(m_Model, glm::radians(1.0f),
            glm::vec3(1.0, 0.3, 0.5));
        m_Shader->setMat4("u_Model"sv, m_Model);
    }

    inline void init(const glfwm::Window& window) noexcept
    {
        auto vertices = std::vector<float>{{
            -0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,
             0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,    1.0f, 1.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f }};

        auto indices = std::vector<unsigned int>{{
            0U, 1U, 2U,
            0U, 2U, 3U,

            4U, 5U, 6U,
            4U, 6U, 7U,

            1U, 5U, 6U,
            1U, 6U, 2U,

            4U, 0U, 3U,
            4U, 3U, 7U,

            0U, 4U, 5U,
            0U, 5U, 1U,

            6U, 7U, 3U,
            6U, 3U, 2U }};

        auto attr = std::array<unsigned int, 2>({3, 3});

        m_Vertices.emplace(attr);
        m_Vertices->addVertices(vertices);
        m_Vertices->addIndices(indices);

        m_Shader.emplace(glfwm::Shader::parse(
            "Resources/Shaders/MVP/vs.glsl"sv,
            "Resources/Shaders/MVP/fs.glsl"sv));

        auto view = glm::translate(glm::mat4(1.0f),
            glm::vec3(0.0f, 0.0f, -3.0f));
        auto proj = glm::perspective(glm::radians(45.0f),
            static_cast<float>(window.getWidth())
                / static_cast<float>(window.getHeight()),
            0.1f, 1000.0f);

        m_Shader->setMat4("u_Model"sv, m_Model);
        m_Shader->setMat4("u_View"sv, view);
        m_Shader->setMat4("u_Projection"sv, proj);
    }

    inline void term() noexcept
    {
        m_Shader.reset();
        m_Vertices.reset();
    }
}
