/*
    Disjoint Set Union (DSU) or Union-Find is a data structure that keeps track
    of elements partitioned into a number of disjoint (non-overlapping) sets.

    It supports two main operations:
    - find(u): Determines the representative (leader) of the set containing u
    - union(u, v): Merges the sets that contain u and v

    It's useful in:
    - Connected components
    - Kruskal's algorithm (Minimum Spanning Tree)
    - Cycle detection in undirected graphs
    - Grouping elements dynamically in sets

    Optimizations:
    - Path Compression: Flattens the tree during find operations for faster future queries.
    - Union by Rank / Size: Always attach the smaller (or lower-rank) tree to the bigger one to keep trees shallow.

    Time Complexity of DSU Operations (Simplified):

    1. Initialization (makeSet): O(n)
       - Each element is its own parent at the start.

    2. find(u): O(1) on average
       - Uses path compression to make future lookups faster.
       - Over time, trees become almost flat.

    3. union(u, v): O(1) on average
       - With union by rank or size, merging is efficient and trees remain shallow.

    Actual Theoretical Complexity:
    - Each operation (find or union) runs in O(α(n)) time,
      where α(n) is the inverse Ackermann function.
    - α(n) grows extremely slowly and is ≤ 5 for all practical values of n.

    So in practice, DSU operations are considered to run in constant time.
*/

class DSU {
private:
    vector<int> parent, rank, size;

public:
    // Constructor to initialize DSU with 'n' elements
    DSU(int n) {
        parent.resize(n + 1); // Parent of each node
        rank.resize(n + 1, 0); // Used for union by rank
        size.resize(n + 1, 1); // Used for union by size

        for (int i = 0; i <= n; i++)
            parent[i] = i; // Initially, each node is its own parent
    }

    // Find operation with path compression
    int find(int u) {
        if (parent[u] != u)
            parent[u] = find(parent[u]); // Path compression
        return parent[u];
    }

    // Union by rank
    void unionByRank(int u, int v) {
        int pu = find(u); // Root of u
        int pv = find(v); // Root of v

        if (pu == pv) return; // Already in the same set

        // Attach smaller rank tree under larger rank tree
        if (rank[pu] < rank[pv]) {
            parent[pu] = pv;
        } else if (rank[pu] > rank[pv]) {
            parent[pv] = pu;
        } else {
            parent[pv] = pu;
            rank[pu]++; // Increase rank if equal
        }
    }

    // Union by size
    void unionBySize(int u, int v) {
        int pu = find(u); // Root of u
        int pv = find(v); // Root of v

        if (pu == pv) return; // Already in the same set

        // Attach smaller size tree under larger size tree
        if (size[pu] < size[pv]) {
            parent[pu] = pv;
            size[pv] += size[pu];
        } else {
            parent[pv] = pu;
            size[pu] += size[pv];
        }
    }

    // Check if two nodes belong to the same set
    bool isConnected(int u, int v) {
        return find(u) == find(v);
    }
};
