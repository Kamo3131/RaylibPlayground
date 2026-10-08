#include "GridGraph.hpp"
#include <cmath>

void GridGraph<Point>::addBlockade(const Point&& blockade, const float width, const float height) {
    m_blockades.emplace(blockade.x - width, blockade.z + height);
    m_blockades.emplace(blockade.x, blockade.z + height);
    m_blockades.emplace(blockade.x + width, blockade.z + height);
    m_blockades.emplace(blockade.x - width, blockade.z);
    m_blockades.emplace(blockade.x, blockade.z);
    m_blockades.emplace(blockade.x + width, blockade.z);
    m_blockades.emplace(blockade.x - width, blockade.z - height);
    m_blockades.emplace(blockade.x, blockade.z - height);
    m_blockades.emplace(blockade.x + width, blockade.z - height);
}

std::vector<Point> GridGraph<Point>::neighbors(const Point& p) {
    std::vector<Point> result;
    std::vector<Point> dirs = {{0.0f, 0.5f}, {0.0f, -0.5f}, {-0.5f, 0.0f}, {0.5f, 0.0f}, {0.5f, 0.5f}, {0.5f, -0.5f}, {-0.5f, 0.5f}, {-0.5f, -0.5f}};
    for (const auto& d : dirs) {
        Point next{p.x + d.x, p.z + d.z};
        
        if (m_blockades.contains(next))
        {
            continue;
        }
        result.push_back(next);
    }
    return result;
}

double GridGraph<Point>::cost(const Point& from, const Point& to) {
    return hypot(from.x - to.x, from.z - to.z);
}

