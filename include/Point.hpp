#ifndef POINT_HPP
#define POINT_HPP
struct Point {
    float x, z;
    bool operator>(const Point& o) const;
    bool operator<(const Point& o) const;
    bool operator==(const Point& o) const;
};

template<typename Location>
inline double heuristic(const Location& a, const Location& b) {
    return hypot(a.x - b.x, a.z - b.z);
}
#endif /* POINT_HPP */
