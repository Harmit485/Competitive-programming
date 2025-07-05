template<typename T>
class SegmentTree {
    int n;                      // Size of the input array
    vector<T> tree;             // Segment tree stored in a flat array of size 2 * n
    T identity;                 // Identity element for the operation (e.g., 0 for sum, INT_MAX for min)
    function<T(T, T)> op;       // The operation to apply (e.g., min, max, sum, gcd)

public:
    // Constructor: Builds the segment tree from input array
    SegmentTree(const vector<T>& arr, T identity, function<T(T, T)> op) {
        this->identity = identity;
        this->op = op;
        n = arr.size();
        tree.resize(2 * n, identity); // Initialize tree with identity elements

        // Fill the leaves with input array elements
        for (int i = 0; i < n; ++i)
            tree[n + i] = arr[i];

        // Build internal nodes by combining child nodes from bottom up
        for (int i = n - 1; i > 0; --i)
            tree[i] = op(tree[2 * i], tree[2 * i + 1]);
    }

    // Update value at index i (0-based in input array) to 'value'
    void update(int i, T value) {
        i += n;            // Move to the corresponding leaf in the tree
        tree[i] = value;   // Update the leaf

        // Move up and update ancestors
        while (i > 1) {
            i >>= 1;       // Move to parent node
            tree[i] = op(tree[2 * i], tree[2 * i + 1]); // Recompute parent from children
        }
    }

    // Query in range [l, r) — half-open interval
    T query(int l, int r) {
        T res_left = identity, res_right = identity; // Initialize results for both ends
        l += n; r += n; // Shift range to leaf level in tree

        while (l < r) {
            // If l is a right child, include it and move to next
            if (l & 1) res_left = op(res_left, tree[l++]);

            // If r is a right child, move to left sibling and include it
            if (r & 1) res_right = op(tree[--r], res_right);

            // Move l and r to parent level
            l >>= 1;
            r >>= 1;
        }

        // Combine left and right result
        return op(res_left, res_right);
    }
};
