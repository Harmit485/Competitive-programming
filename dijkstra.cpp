/*
    Dijkstra's Algorithm is a classic graph algorithm for finding the shortest path
    from a single source node to all other nodes in a graph with non-negative edge weights.

    It is a greedy algorithm that always expands the node with the smallest known cost
    from the source, using a priority queue (min-heap) to efficiently select the next node.

    Core Concepts:
    - distance[u]: Stores the minimum cost to reach node u from the source.
    - Priority Queue: Stores pairs {cost, node} to always process the least-cost node next.
    - Lazy Updates: If a node is pulled from the queue with an outdated cost, it's skipped.

    Use Cases:
    - Network routing protocols (e.g., OSPF)
    - Shortest path in road maps, games, and GPS systems
    - Any domain where optimal cost/resource/time from a source is needed

    Requirements:
    - Graph must have non-negative edge weights
    - Directed or undirected graphs are both supported

    Time Complexity:
    - Using Min-Heap (Binary Heap):
        O((V + E) * log V)
        where V = number of vertices, E = number of edges

    Space Complexity:
    - O(V + E) for adjacency list
    - O(V) for distance array
    - O(V) for the priority queue (in worst case)

    Limitations:
    - Cannot handle negative edge weights (use Bellman-Ford instead)

    Optimizations:
    - Early Stopping: If only the shortest path to a target node is required
    - Fibonacci Heap (theoretical): Improves complexity to O(E + V log V) but rarely used in practice

    In practice, with binary heaps and adjacency lists, Dijkstra is fast and widely applicable.
*/

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
