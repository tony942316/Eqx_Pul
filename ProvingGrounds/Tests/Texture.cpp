export module GlfwMod.Tests.Texture;

import Equinox;
import Eqx.GlfwMod;

namespace glfwmod::tests::texture
{
    constinit auto m_Shader = std::optional<glfwm::Shader>{};
    constinit auto m_Vertices = std::optional<glfwm::VertexArray>{};
    constinit auto m_Texture = std::optional<glfwm::Texture>{};

    export inline void run() noexcept;
    export inline void init() noexcept;
    export inline void term() noexcept;
}

namespace glfwmod::tests::texture
{
    inline void run() noexcept
    {
        glfwm::Texture::enableSlot(0U);
        m_Texture->enable();
        glfwm::renderer::draw(m_Shader.value(), m_Vertices.value());
    }

    inline void init() noexcept
    {
        auto vertices = std::array<float, 20>{
            0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
        };

        auto indices = std::array<unsigned int, 6>{
            0, 1, 3,
            1, 2, 3
        };

        auto attr = std::array<unsigned int, 2>{3, 2};

        m_Vertices.emplace(attr);
        m_Vertices->addVertices(vertices);
        m_Vertices->addIndices(indices);

        m_Shader.emplace(glfwm::Shader::parse(
            "Resources/Shaders/Texture/vs.glsl"sv,
            "Resources/Shaders/Texture/fs.glsl"sv));

        m_Shader->setInt("texture0", 0);

        m_Texture.emplace("Resources/Textures/BrickWall.png"sv);
    }

    inline void term() noexcept
    {
        m_Shader.reset();
        m_Vertices.reset();
        m_Texture.reset();
    }
}
