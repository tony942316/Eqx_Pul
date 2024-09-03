export module Eqx.Pul.CQuad;

import <Eqx/std.hpp>;

import <Eqx/TPL/glad/glad.hpp>;
import <Eqx/TPL/glm/glm.hpp>;

import <Eqx/Lib/Macros.hpp>;
import Eqx.Lib;

export namespace eqx
{
    class CQuad
    {
    public:
        struct Color { std::uint8_t r, g, b; };

        CQuad() = default;
        CQuad(const CQuad&) = default;
        CQuad(CQuad&&) = default;
        CQuad& operator= (const CQuad&) = default;
        CQuad& operator= (CQuad&&) = default;
        ~CQuad() = default;

        inline void setRect(const eqx::Rectangle<float>& rect) noexcept;

        inline void setPos(const eqx::Point<float>& point) noexcept;

        inline void setZ(float z) noexcept;

        inline void setColor(const Color& color) noexcept;

        [[nodiscard]] inline const eqx::Rectangle<float>&
            getRect() const noexcept;

        [[nodiscard]] inline eqx::Point<float> getPos() const noexcept;

        [[nodiscard]] inline float getZ() const noexcept;

        [[nodiscard]] inline const Color& getColor() const noexcept;

    private:
        eqx::Rectangle<float> m_Rect;
        float m_Z;
        Color m_Color;
    };
}

namespace eqx
{
    inline void CQuad::setRect(const eqx::Rectangle<float>& rect) noexcept
    {
        m_Rect = rect;
    }

    inline void CQuad::setPos(const eqx::Point<float>& point) noexcept
    {
        m_Rect.setLocation(point);
    }

    inline void CQuad::setZ(float z) noexcept
    {
        m_Z = z;
    }

    inline void CQuad::setColor(const Color& color) noexcept
    {
        m_Color = color;
    }

    [[nodiscard]] inline const eqx::Rectangle<float>&
        CQuad::getRect() const noexcept
    {
        return m_Rect;
    }

    [[nodiscard]] inline eqx::Point<float> CQuad::getPos() const noexcept
    {
        return m_Rect.getTopLeftPoint();
    }

    [[nodiscard]] inline float CQuad::getZ() const noexcept
    {
        return m_Z;
    }

    [[nodiscard]] inline const CQuad::Color& CQuad::getColor() const noexcept
    {
        return m_Color;
    }
}
