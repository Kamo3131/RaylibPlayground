#ifndef ASTAR_HPP
#define ASTAR_HPP
#include <map>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <map>
#include "Point.hpp"

template<typename Location, typename ReturnType>
ReturnType reconstructPath(const std::map<Location, Location>& came_from, const Location& start, const Location& end) {
    ReturnType path;
    Location current = end;
    if(came_from.find(end) == came_from.end()) {
        return path;
    }
    while (!(current == start)) {
        path.push_back(current);
        current = came_from.at(current);
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    return path;
}

template<typename Location, typename Graph, typename ReturnType>
ReturnType aStar(Graph& graph, const Location& start, const Location& target) {
    using PQElement = std::pair<double, Location>;
    std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement>> openSet;
    
    std::map<Location, double> g_scores;
    std::map<Location, Location> came_from;

    g_scores[start] = 0;
    openSet.push({heuristic(start, target), start});
    came_from[start] = start;

    while(!openSet.empty())
    {
        const auto [current_f, current] = openSet.top();
        openSet.pop();

        if(current == target) {
            return reconstructPath<Location, ReturnType>(std::move(came_from), start, current);
        }

        if (current_f > g_scores[current] + heuristic(current, target)) {
            continue;
        }

        for (const Location& next : graph.neighbors(current)) {
            double new_cost = g_scores[current] + graph.cost(current, next); 
            
            if(g_scores.find(next) == g_scores.end() || new_cost < g_scores[next]) {
                g_scores[next] = new_cost;
                double f_score = new_cost + heuristic(next, target);
                openSet.push({f_score, next});
                came_from[next] = current;
            }
        }
    }

    std::cout << "Path not found!\n";
    return ReturnType();  
}

#endif /* ASTAR_HPP */
