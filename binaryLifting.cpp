/*
    Binary Lifting — Only for k-th Ancestor Queries (from parent array + root)

    Purpose:
    - Efficiently find the k-th ancestor of any node in a rooted tree.

    Assumptions:
    - Tree is rooted.
    - No cycles (standard tree structure).

    Core Idea:
    - Precompute 2^j-th ancestors for each node using dynamic programming.
    - To jump up k levels from a node u, break k into powers of 2 and jump accordingly.

    Time Complexity:
    - Preprocessing: O(n * log n)
    - Each lift(u, k): O(log k)
*/

class BinaryLifting {
public:
    int n, LOG;
    vector<vector<int>> up; // up[i][j] = 2^j-th ancestor of node i

    // Constructor: build the lifting table from parent array and root
    BinaryLifting(const vector<int>& par, int root) {
        n = par.size();
        LOG = 32 - __builtin_clz(n); // ceil(log2(n))
        up.assign(n, vector<int>(LOG));

        // Fill 2^0-th ancestor (i.e., direct parent)
        for (int i = 0; i < n; ++i)
            up[i][0] = par[i];

        up[root][0] = root; // Ensure root points to itself

        // Precompute 2^j-th ancestors for all nodes
        for (int j = 1; j < LOG; ++j) {
            for (int i = 0; i < n; ++i) {
                up[i][j] = up[up[i][j - 1]][j - 1];
            }
        }
    }

    // Function to lift a node `u` by `k` levels up in the tree
    int lift(int u, int k) {
        for (int j = 0; j < LOG; ++j) {
            if (k & (1 << j)) {
                u = up[u][j]; // Jump 2^j steps up
            }
        }
        return u;
    }
};
