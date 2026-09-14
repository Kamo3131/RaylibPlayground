#include "Square.hpp"
#include <numbers>

Square::Square(const float length, const float size) : m_length{length}, m_size{size} {}
void Square::DrawSquare(const Vector3 origin, const Color color) const {
    DrawPlane({origin.x, origin.y + 0.01f, origin.z + m_length}, {m_length * 2 + 2 * m_size, 2 * m_size}, color);
    DrawPlane({origin.x + m_length, origin.y + 0.01f, origin.z}, {2 * m_size, m_length * 2 + 2 * m_size}, color);
    DrawPlane({origin.x, origin.y + 0.01f, origin.z - m_length}, {m_length * 2 + 2 * m_size, 2 * m_size}, color);
    DrawPlane({origin.x - m_length, origin.y + 0.01f, origin.z}, {2 * m_size, m_length * 2 + 2 * m_size}, color);
}

void Square::SetLength(const float length) 
{
    m_length = length;
}
[[nodiscard]] float Square::GetLength() const 
{
    return m_length;
}
void Square::SetSize(const float size) 
{
    m_size = size;
}
[[nodiscard]] float Square::GetSize() const 
{
    return m_size;
}