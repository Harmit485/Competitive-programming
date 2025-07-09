/*
    A Segment Tree is a binary tree data structure used for:
    - Efficient **range queries** (like sum, min, max, GCD, etc.)
    - Efficient **point updates** (changing a single value in the array)

    Key Idea:
    - Divide the array into segments and store results for each segment in a tree.
    - For an array of size `n`, the tree is built in O(n) time and takes about 4 * n space.

    Operations Supported:

    1. Build: O(n)
       - Construct the tree from the array in a bottom-up manner.

    2. Query(L, R): O(log n)
       - Query for a result (like sum/min/max) in the range [L, R).
       - The range is split into log(n) segments at most.

    3. Update(index, value): O(log n)
       - Update the value at a specific index.
       - Only the affected path from leaf to root is updated.

    Why use Segment Trees?
    - Brute force takes O(n) per query/update. Segment Tree reduces it to O(log n).
    - Great for situations with:
        → Many range queries
        → Many point updates
        → Changing data (unlike prefix sums)

    Notes:
    - Tree is usually stored as a flat array of size ~2*n or 4*n.
    - Leaf nodes represent array elements.
    - Internal nodes store combined results of children.

    Common use cases:
    - Range sum/min/max/GCD
    - Real-time analytics over sliding windows
*/

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
