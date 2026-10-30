#include "Point.hpp"
#include <cmath>
bool Point::operator>(const Point& o) const {
    return x > o.x || (x == o.x && z > o.z);
}

bool Point::operator<(const Point& o) const {
    return x < o.x || (x == o.x && z < o.z);
}

bool Point::operator==(const Point& o) const {
    return std::abs(x - o.x) < 0.01f && std::abs(z - o.z) < 0.01f;
}

