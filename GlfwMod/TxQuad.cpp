export module Eqx.GlfwMod.TxQuad;

import <Eqx/std.hpp>;

import <Eqx/TPL/glad/glad.hpp>;
import <Eqx/TPL/glm/glm.hpp>;

import <Eqx/Lib/Macros.hpp>;
import Eqx.Lib;

import Eqx.GlfwMod.Texture;

export namespace glfwm
{
    class TxQuad
    {
    public:
        TxQuad() = default;
        TxQuad(const TxQuad&) = default;
        TxQuad(TxQuad&&) = default;
        TxQuad& operator= (const TxQuad&) = default;
        TxQuad& operator= (TxQuad&&) = default;
        ~TxQuad() = default;

        inline void setRect(const eqx::Rectangle<float>& rect) noexcept;

        inline void setPos(const eqx::Point<float>& point) noexcept;

        inline void setZ(float z) noexcept;

        inline void setTexture(const Texture& texture) noexcept;

        [[nodiscard]] inline const eqx::Rectangle<float>&
            getRect() const noexcept;

        [[nodiscard]] inline eqx::Point<float> getPos() const noexcept;

        [[nodiscard]] inline float getZ() const noexcept;

        [[nodiscard]] inline const Texture& getTexture() const noexcept;

    private:
        eqx::Rectangle<float> m_Rect;
        float m_Z;
        const Texture* m_Texture;
    };
}

namespace glfwm
{
    inline void TxQuad::setRect(const eqx::Rectangle<float>& rect) noexcept
    {
        m_Rect = rect;
    }

    inline void TxQuad::setPos(const eqx::Point<float>& point) noexcept
    {
        m_Rect.setLocation(point);
    }

    inline void TxQuad::setZ(float z) noexcept
    {
        m_Z = z;
    }

    inline void TxQuad::setTexture(const Texture& texture) noexcept
    {
        m_Texture = &texture;
    }

    [[nodiscard]] inline const eqx::Rectangle<float>&
        TxQuad::getRect() const noexcept
    {
        return m_Rect;
    }

    [[nodiscard]] inline eqx::Point<float> TxQuad::getPos() const noexcept
    {
        return m_Rect.getTopLeftPoint();
    }

    [[nodiscard]] inline float TxQuad::getZ() const noexcept
    {
        return m_Z;
    }

    [[nodiscard]] inline const Texture&
        TxQuad::getTexture() const noexcept
    {
        return *m_Texture;
    }
}
