#pragma once

#include <vector>
class IPathFinding {
    public:
        ~IPathFinding() = default;
        //distance, points
        virtual const std::vector<int> get_shortest_path(const int src) const = 0;
};