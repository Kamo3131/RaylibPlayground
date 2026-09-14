#ifndef BLOCKADE_HPP
#define BLOCKADE_HPP
#include "raylib-cpp.hpp"

class Blockade {
    private:
    Vector3 m_position;
    Vector3 m_size;
    raylib::Color m_color;
    public:
    Blockade(const Vector3 position, const Vector3 size, const raylib::Color color);
    ~Blockade() = default;
    void SetPosition(const Vector3 position);
    [[nodiscard]] Vector3 GetPosition() const;
    void SetSize(const Vector3 size);
    [[nodiscard]] Vector3 GetSize() const;
    void SetColor(const raylib::Color color);
    [[nodiscard]] raylib::Color GetColor() const;
    bool PositionIntersects(const Vector3& position, const Vector3& size) const;
    void Draw() const;
};

#endif /* BLOCKADE_HPP */
