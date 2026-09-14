#pragma once

#include "PathFinding.hpp"

class Dijkstra : public IPathFinding {
    private:
        std::vector<std::vector<std::pair<int, int>>> m_nodes;
    public:
        Dijkstra(const std::vector<std::vector<std::pair<int, int>>> nodes);
        ~Dijkstra() = default;
        const std::vector<int> get_shortest_path(const int src) const;
};
