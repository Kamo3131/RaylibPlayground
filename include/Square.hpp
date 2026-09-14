#ifndef SQUARE_HPP
#define SQUARE_HPP
#include <utility>
#include "raylib-cpp.hpp"

class Square {
    private:
        float m_length;
        float m_size;
    public:
        Square(const float length, const float size);
        ~Square() = default;
        void DrawSquare(const Vector3 origin, const Color color) const;
        void SetLength(const float length);
        [[nodiscard]] float GetLength() const;
        void SetSize(const float size);
        [[nodiscard]] float GetSize() const;
};
#endif /* SQUARE_HPP */
