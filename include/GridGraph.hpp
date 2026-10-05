#ifndef GRIDGRAPH_HPP
#define GRIDGRAPH_HPP

#include "Point.hpp"
#include <vector>
#include <set>

template<typename Location>
struct GridGraph {
    void addBlockade(const Location&& blockade, const float width, const float height);
    std::set<Location> m_blockades;
    std::vector<Location> neighbors(const Location& p);
    double cost(const Location& from, const Location& to);
};
template<>
struct GridGraph<Point> {
    void addBlockade(const Point&& blockade, const float width, const float height);
    std::set<Point> m_blockades;
    std::vector<Point> neighbors(const Point& p);
    double cost(const Point& from, const Point& to);
};

#endif /* GRIDGRAPH_HPP */
