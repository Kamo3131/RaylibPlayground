#include <Dijkstra.hpp>
#include <queue>
#include <climits>

Dijkstra::Dijkstra(const std::vector<std::vector<std::pair<int, int>>> nodes) : m_nodes{nodes}{}
const std::vector<int> Dijkstra::get_shortest_path(const int src) const {
    int num_nodes = m_nodes.size();

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    std::vector<int> dist(num_nodes, INT_MAX);
    dist[src] = 0;
    pq.emplace(0, src);
    while(!pq.empty()) {
        auto top = pq.top();
        pq.pop();

        int distance = top.first;
        int node = top.second;

        if (distance > dist[node]) continue;

        for (auto &p : m_nodes[node]) {
            int pair_node = p.first;
            int pair_distance = p.second;

            if (dist[node] + pair_distance < dist[pair_node]) {
                dist[pair_node] = dist[node] + pair_distance;
                pq.emplace(dist[pair_node], pair_node); 
            }
        }
    }
    return dist;
}