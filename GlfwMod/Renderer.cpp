module;

#include <glad/glad.h>
#include <Equinox/Macros.hpp>

export module Eqx.GlfwMod.Renderer;

import Equinox;

import Eqx.GlfwMod.Shader;
import Eqx.GlfwMod.VertexArray;

export namespace glfwm::renderer
{
    using namespace eqx::literals;

    inline void draw(const Shader& shader,
        const VertexArray& vertexArray) noexcept;
}

namespace glfwm::renderer
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
}
