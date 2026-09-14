#include "Blockade.hpp"

    Blockade::Blockade(const Vector3 position, const Vector3 size, const raylib::Color color = raylib::Color::DarkGray()) : m_position{position}, m_size{size}, m_color{color} {}
    void Blockade::SetPosition(const Vector3 position)
    {
        m_position = position;
    }
    [[nodiscard]] Vector3 Blockade::GetPosition() const
    {
        return m_position;
    }

    void Blockade::SetSize(const Vector3 size)
    {
        m_size = size;
    }
    [[nodiscard]] Vector3 Blockade::GetSize() const
    {
        return m_size;
    }

    void Blockade::SetColor(const raylib::Color color)
    {
        m_color = color;
    }
    [[nodiscard]] raylib::Color Blockade::GetColor() const
    {
        return m_color;
    }

    bool Blockade::PositionIntersects(const Vector3& position, const Vector3& size) const
    {
        bool result = true;
        if (abs(m_position.x - position.x) - m_size.x - size.x >= 0.0f)
        {
            result = false;
        }
        if (abs(m_position.y - position.y) - m_size.y - size.y >= 0.0f)
        {
            result = false;
        }
        if (abs(m_position.z - position.z) - m_size.z - size.z >= 0.0f)
        {
            result = false;
        }
        return result;
    }

    void Blockade::Draw() const
    {
        DrawCubeV(m_position, {m_size.x * 2, m_size.y * 2, m_size.z * 2}, m_color);
    }