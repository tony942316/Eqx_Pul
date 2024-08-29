export module GlfwMod.Tests.MVP;

import <Eqx/std.hpp>;

import Eqx.Lib;

import <glm/glm.hpp>;
import <glm/gtc/matrix_transform.hpp>;

import Eqx.GlfwMod;

namespace glfwmod::tests::mvp
{
    constinit auto m_Shader = std::optional<glfwm::Shader>{};
    constinit auto m_Vertices = std::optional<glfwm::VertexArray>{};
    constinit auto m_Texture = std::optional<glfwm::Texture>{};

    export inline void run() noexcept;
    export inline void init() noexcept;
    export inline void term() noexcept;
}

namespace glfwmod::tests::mvp
{
    inline void run() noexcept
    {
        glfwm::renderer::draw(m_Shader.value(), m_Vertices.value());
    }

    inline void init() noexcept
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

        auto view = glm::mat4(1.0f);
        auto proj = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        proj = glm::perspective(1.5708f, 680.0f / 400.0f , 0.1f, 1000.0f);

        //m_Shader->setMat4("u_Model"sv, );
        m_Shader->setMat4("u_View"sv, view);
        m_Shader->setMat4("u_Projection"sv, proj);

        //m_Shader->setInt("texture0"sv, 0);

        m_Texture.emplace("Resources/Textures/BrickWall.png"sv);
    }

    inline void term() noexcept
    {
        m_Shader.reset();
        m_Vertices.reset();
        m_Texture.reset();
    }
}
