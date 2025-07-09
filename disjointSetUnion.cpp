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
