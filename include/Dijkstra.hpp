#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include <map>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <map>
#include "ReconstructPath.hpp"

template<typename Location, typename Graph, typename ReturnType>
ReturnType dijkstra(Graph& graph, const Location& start, const Location& target) {
    if (start == target) 
    {
        return ReturnType();
    }
    if (graph.fieldIsBlockade(target)) 
    {
        return ReturnType();
    }

    using PQElement = std::pair<double, Location>;
    std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement>> openSet;
    
    std::map<Location, double> distance;
    std::map<Location, Location> came_from;

    distance[start] = 0;
    openSet.push({distance[start], start});
    came_from[start] = start;

    while(!openSet.empty())
    {
        const auto [current_f, current] = openSet.top();
        openSet.pop();
        if(current == target) {
            return reconstructPath<Location, ReturnType>(std::move(came_from), start, current);
        }
        for (const Location& next : graph.neighbors(current)) {
            double new_cost = distance[current] + graph.cost(current, next); 
            if(distance.find(next) == distance.end() || new_cost < distance[next]) {
                distance[next] = new_cost;
                double f_score = new_cost;
                openSet.push({f_score, next});
                came_from[next] = current;
            }
        }
    }

    std::cout << "Path not found!\n";
    return ReturnType();  
}

#endif /* DIJKSTRA_HPP */
