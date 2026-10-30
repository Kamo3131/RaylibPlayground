#ifndef RECONSTRUCTPATH_HPP
#define RECONSTRUCTPATH_HPP
#include <map>

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

#endif /* RECONSTRUCTPATH_HPP */
