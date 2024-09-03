export module Eqx.Pul.Renderer;

import <Eqx/std.hpp>;

import <Eqx/TPL/glad/glad.hpp>;

import <Eqx/Lib/Macros.hpp>;
import Eqx.Lib;

import Eqx.Pul.Window;
import Eqx.Pul.Shader;
import Eqx.Pul.VertexArray;
import Eqx.Pul.Texture;
import Eqx.Pul.CQuad;
import Eqx.Pul.TxQuad;

export namespace eqx::renderer
{
    inline void draw(const Shader& shader,
        const VertexArray& vertexArray) noexcept;

    inline void draw(const Shader& shader, const VertexArray& vertexArray,
        const Texture& texture) noexcept;

    inline void draw(const Shader& shader, const CQuad& quad) noexcept;

    inline void draw(const Shader& shader, const TxQuad& quad) noexcept;
}

namespace eqx::renderer
{
    inline void draw(const Shader& shader,
        const VertexArray& vertexArray) noexcept
    {
        shader.enable();
        vertexArray.enable();

        glDrawElements(GL_TRIANGLES,
            static_cast<int>(vertexArray.getIndexCount()),
            GL_UNSIGNED_INT, 0);
    }

    inline void draw(const Shader& shader, const VertexArray& vertexArray,
        const Texture& texture) noexcept
    {
        eqx::Texture::enableSlot(0U);
        texture.enable();

        shader.enable();
        vertexArray.enable();

        glDrawElements(GL_TRIANGLES,
            static_cast<int>(vertexArray.getIndexCount()),
            GL_UNSIGNED_INT, 0);
    }

    inline void draw(const Shader& shader, const CQuad& quad) noexcept
    {
        auto vertices = std::array<float, 24>{
            0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f
        };

        vertices.at(0_uz) = quad.getRect().getTopRightPoint().x;
        vertices.at(1_uz) = quad.getRect().getTopRightPoint().y;
        vertices.at(2_uz) = -quad.getZ();

        vertices.at(3_uz) = static_cast<float>(quad.getColor().r) / 255.0f;
        vertices.at(4_uz) = static_cast<float>(quad.getColor().g) / 255.0f;
        vertices.at(5_uz) = static_cast<float>(quad.getColor().b) / 255.0f;

        vertices.at(6_uz) = quad.getRect().getBottomRightPoint().x;
        vertices.at(7_uz) = quad.getRect().getBottomRightPoint().y;
        vertices.at(8_uz) = -quad.getZ();

        vertices.at(9_uz) = static_cast<float>(quad.getColor().r) / 255.0f;
        vertices.at(10_uz) = static_cast<float>(quad.getColor().g) / 255.0f;
        vertices.at(11_uz) = static_cast<float>(quad.getColor().b) / 255.0f;

        vertices.at(12_uz) = quad.getRect().getBottomLeftPoint().x;
        vertices.at(13_uz) = quad.getRect().getBottomLeftPoint().y;
        vertices.at(14_uz) = -quad.getZ();

        vertices.at(15_uz) = static_cast<float>(quad.getColor().r) / 255.0f;
        vertices.at(16_uz) = static_cast<float>(quad.getColor().g) / 255.0f;
        vertices.at(17_uz) = static_cast<float>(quad.getColor().b) / 255.0f;

        vertices.at(18_uz) = quad.getRect().getTopLeftPoint().x;
        vertices.at(19_uz) = quad.getRect().getTopLeftPoint().y;
        vertices.at(20_uz) = -quad.getZ();

        vertices.at(21_uz) = static_cast<float>(quad.getColor().r) / 255.0f;
        vertices.at(22_uz) = static_cast<float>(quad.getColor().g) / 255.0f;
        vertices.at(23_uz) = static_cast<float>(quad.getColor().b) / 255.0f;

        auto indices = std::array<unsigned int, 6>{
            0U, 1U, 3U,
            1U, 2U, 3U
        };

        auto attr = std::array<unsigned int, 2>{3, 3};

        auto va = VertexArray{attr};
        va.addVertices(vertices);
        va.addIndices(indices);

        draw(shader, va);
    }

    inline void draw(const Shader& shader, const TxQuad& quad) noexcept
    {
        auto vertices = std::array<float, 20>{
            0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.0f, 0.0f, 0.0f
        };

        vertices.at(0_uz) = quad.getRect().getTopRightPoint().x;
        vertices.at(1_uz) = quad.getRect().getTopRightPoint().y;
        vertices.at(2_uz) = -quad.getZ();

        vertices.at(3_uz) = 1.0f;
        vertices.at(4_uz) = 1.0f;

        vertices.at(5_uz) = quad.getRect().getBottomRightPoint().x;
        vertices.at(6_uz) = quad.getRect().getBottomRightPoint().y;
        vertices.at(7_uz) = -quad.getZ();

        vertices.at(8_uz) = 1.0f;
        vertices.at(9_uz) = 0.0f;

        vertices.at(10_uz) = quad.getRect().getBottomLeftPoint().x;
        vertices.at(11_uz) = quad.getRect().getBottomLeftPoint().y;
        vertices.at(12_uz) = -quad.getZ();

        vertices.at(13_uz) = 0.0f;
        vertices.at(14_uz) = 0.0f;

        vertices.at(15_uz) = quad.getRect().getTopLeftPoint().x;
        vertices.at(16_uz) = quad.getRect().getTopLeftPoint().y;
        vertices.at(17_uz) = -quad.getZ();

        vertices.at(18_uz) = 0.0f;
        vertices.at(19_uz) = 1.0f;

        auto indices = std::array<unsigned int, 6>{
            0U, 1U, 3U,
            1U, 2U, 3U
        };

        auto attr = std::array<unsigned int, 2>{3, 2};

        auto va = VertexArray{attr};
        va.addVertices(vertices);
        va.addIndices(indices);

        draw(shader, va, quad.getTexture());
    }
}
