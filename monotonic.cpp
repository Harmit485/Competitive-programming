/*
===================
MONOTONIC STACK
===================

Use When:
- Need to find Next/Previous Greater or Smaller element
- One-time scan of the array (static, not sliding)

Core Idea:
- Maintain a stack that is either increasing or decreasing
- While current element breaks monotonicity, pop from stack
*/

for each index i in array:
    while (!st.empty() && current breaks monotonicity with st.top()):
        // process st.top() (e.g., assign result, pop)
        st.pop()
    st.push(i or value)

/*
Monotonicity Choice:
- Increasing Stack → use for Next Smaller or Previous Smaller
- Decreasing Stack → use for Next Greater or Previous Greater

Direction:
- Left to Right → Next element type
- Right to Left → Previous element type

Examples:
- Next Greater: while (!st.empty() && arr[i] > arr[st.top()])
- Next Smaller: while (!st.empty() && arr[i] < arr[st.top()])

Time Complexity: O(n) total because each element is pushed & popped once
*/


/*
====================
MONOTONIC QUEUE
====================

Use When:
- Need min or max in a sliding window (dynamic range)

Core Idea:
- Maintain a deque that stores only useful candidates
- Remove:
  - From front → if out of window
  - From back → if worse than current
*/

for each index i in array:
    // Remove out-of-window elements
    if (!dq.empty() && dq.front() <= i - k)
        dq.pop_front()

    // Maintain monotonicity
    while (!dq.empty() && current breaks monotonicity with dq.back()):
        dq.pop_back()

    dq.push_back(i)

    // Record result when window is full
    if (i >= k - 1):
        res.push_back(arr[dq.front()])

/*
Monotonicity Choice:
- Decreasing Queue → for Maximum in window
- Increasing Queue → for Minimum in window

Comparison:
- For max: while (arr[i] >= arr[dq.back()])
- For min: while (arr[i] <= arr[dq.back()])

Time Complexity: O(n) total for entire array
*/
