#ifndef POINT_HPP
#define POINT_HPP
struct Point {
    float x, z;
    bool operator>(const Point& o) const;
    bool operator<(const Point& o) const;
    bool operator==(const Point& o) const;
};
#endif /* POINT_HPP */
