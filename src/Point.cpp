#include "Point.hpp"
#include <cmath>
bool Point::operator>(const Point& o) const {
    return x > o.x || (x == o.x && z > o.z);
}

bool Point::operator<(const Point& o) const {
    return x < o.x || (x == o.x && z < o.z);
}

bool Point::operator==(const Point& o) const {
    return x == o.x && z == o.z;
}


