module;

#include <glad/glad.h>
#include <Equinox/Macros.hpp>

export module Eqx.GlfwMod.VertexArray;

import Equinox;

export namespace glfwm
{
    class VertexArray
    {
    public:
        explicit inline VertexArray(std::span<unsigned int> attribs) noexcept;
        inline VertexArray(VertexArray&& other) noexcept;
        inline VertexArray& operator= (VertexArray&& other) noexcept;
        inline ~VertexArray() noexcept;

        VertexArray(const VertexArray&) = delete;
        VertexArray& operator= (const VertexArray&) = delete;

        inline void addVertices(std::span<float> vertices) const noexcept;
        inline void addIndices(std::span<unsigned int> indices) const noexcept;

        inline void enable() const noexcept;
        inline void disable() const noexcept;

    private:
        unsigned int m_VA;
        unsigned int m_VB;
        unsigned int m_EB;
    };
}

namespace glfwm
{
    inline VertexArray::VertexArray(std::span<unsigned int> attribs) noexcept
    {
        glGenVertexArrays(1, &m_VA);
        glGenBuffers(1, &m_VB);
        glGenBuffers(1, &m_EB);

        enable();

        glBindBuffer(GL_ARRAY_BUFFER, m_VB);

        auto vertexSize = std::reduce(std::ranges::cbegin(attribs),
            std::ranges::cend(attribs), 0U, std::plus<>{}) * sizeof(float);
        auto runningCount = 0U;

        for (int i = 0; i < std::ranges::size(attribs); i++)
        {
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, attribs[i], GL_FLOAT, GL_FALSE,
                vertexSize, (void*)(runningCount * sizeof(float)));
            runningCount += attribs[i];
        }

        glBindBuffer(GL_ARRAY_BUFFER, 0U);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EB);

        disable();

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0U);
    }

    inline VertexArray::VertexArray(VertexArray&& other) noexcept
        :
        m_VA(std::move(other.m_VA)),
        m_VB(std::move(other.m_VB)),
        m_EB(std::move(other.m_EB))
    {
        other.m_VA = 0U;
    }

    inline VertexArray& VertexArray::operator= (VertexArray&& other) noexcept
    {
        eqx::ENSURE_HARD(this != &other, "Can't Move Into Itself!!!"sv);

        std::swap(m_VA, other.m_VA);
        std::swap(m_VB, other.m_VB);
        std::swap(m_EB, other.m_EB);
        return *this;
    }

    inline VertexArray::~VertexArray() noexcept
    {
        if (m_VA != 0U)
        {
            glDeleteVertexArrays(1, &m_VA);
            glDeleteBuffers(1, &m_VB);
            glDeleteBuffers(1, &m_EB);
        }
    }

    inline void VertexArray::addVertices(
        std::span<float> vertices) const noexcept
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_VB);
        glBufferData(GL_ARRAY_BUFFER,
            std::ranges::size(vertices) * sizeof(float), vertices.data(),
            GL_STATIC_DRAW);
    }

    inline void VertexArray::addIndices(
        std::span<unsigned int> indices) const noexcept
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EB);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
            std::ranges::size(indices) * sizeof(unsigned int), indices.data(),
            GL_STATIC_DRAW);
    }

    inline void VertexArray::enable() const noexcept
    {
        glBindVertexArray(m_VA);
    }

    inline void VertexArray::disable() const noexcept
    {
        glBindVertexArray(0U);
    }
}
