const int INF = 1e9; // Change to LLONG_MAX for long long

using Cost = int;
using Node = int;
using Adjacent = pair<Node, Cost>;        // {neighbor, cost}
using HeapEntry = pair<Cost, Node>;       // {totalCost, node}

vector<Cost> dijkstra(int nodeCount, int source, const vector<vector<Adjacent>>& adjacency) {
    vector<Cost> minCost(nodeCount, INF);
    priority_queue<HeapEntry, vector<HeapEntry>, greater<>> minHeap;

    minCost[source] = 0;
    minHeap.push({0, source});

    while (!minHeap.empty()) {
        auto [currCost, u] = minHeap.top();
        minHeap.pop();

        if (currCost > minCost[u]) continue;

        for (const auto& [v, weight] : adjacency[u]) {
            Cost nextCost = currCost + weight;
            if (nextCost < minCost[v]) {
                minCost[v] = nextCost;
                minHeap.push({nextCost, v});
            }
        }
    }

    return minCost;
}
