#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

// Structure representing a Fenwick Tree (Binary Indexed Tree)
struct FenwickTree {
    int size;
    std::vector<int> tree;

    // Constructor to initialize Fenwick Tree with a given size
    FenwickTree(int n) : size(n), tree(n + 1, 0) {}

    // Update the tree at position 'index' by adding 'value'
    void update(int index, int value) {
        while (index <= size) {
            tree[index] += value;
            index += index & -index;
        }
    }

    // Query the cumulative frequency up to position 'index'
    int query(int index) const {
        int result = 0;
        while (index > 0) {
            result += tree[index];
            index -= index & -index;
        }
        return result;
    }

    // Query the cumulative frequency in the range [left, right]
    int rangeQuery(int left, int right) const {
        if (left > right) return 0;
        return query(right) - query(left - 1);
    }
};

// Structure representing an interval with left and right bounds and a requirement
struct Interval {
    long long left;
    long long right;
    int requiredTrees;
};

// Function to process each test case
void processTestCase() {
    int numberOfTrees, numberOfIntervals;
    std::cin >> numberOfTrees >> numberOfIntervals;

    // Read tree positions
    std::vector<long long> treePositions(numberOfTrees);
    for (auto &position : treePositions) {
        std::cin >> position;
    }
    std::sort(treePositions.begin(), treePositions.end());

    // Read intervals
    std::vector<Interval> intervals(numberOfIntervals);
    for (auto &interval : intervals) {
        std::cin >> interval.left >> interval.right >> interval.requiredTrees;
    }

    // Sort intervals based on the right bound, then left bound
    std::sort(intervals.begin(), intervals.end(), [](const Interval &a, const Interval &b) {
        if (a.right != b.right)
            return a.right < b.right;
        return a.left < b.left;
    });

    // Initialize Fenwick Tree and a set to keep track of not chosen trees
    FenwickTree fenwick(numberOfTrees);
    std::set<int> notChosenTrees;
    for (int i = 1; i <= numberOfTrees; ++i) {
        notChosenTrees.insert(i);
    }

    // Process each interval
    for (const auto &interval : intervals) {
        // Find the range of trees within the current interval
        int startIndex = std::lower_bound(treePositions.begin(), treePositions.end(), interval.left) - treePositions.begin() + 1;
        int endIndex = std::upper_bound(treePositions.begin(), treePositions.end(), interval.right) - treePositions.begin();

        // If no trees fall within the interval, continue to the next interval
        if (startIndex > endIndex) continue;

        // Calculate the number of trees already chosen in this interval
        int alreadyChosen = fenwick.rangeQuery(startIndex, endIndex);
        int treesNeeded = interval.requiredTrees - alreadyChosen;

        // If no additional trees are needed, continue to the next interval
        if (treesNeeded <= 0) continue;

        // Iterate from the end of the interval to choose trees
        auto it = notChosenTrees.upper_bound(endIndex);
        if (it != notChosenTrees.begin()) {
            --it;
        }

        while (treesNeeded > 0 && it != notChosenTrees.end() && *it >= startIndex) {
            int treeIndex = *it;
            fenwick.update(treeIndex, 1);
            it = notChosenTrees.erase(it);
            if (it != notChosenTrees.begin()) {
                --it;
            }
            --treesNeeded;
        }
    }

    // Calculate the number of chosen trees and output the result
    int totalChosen = fenwick.query(numberOfTrees);
    std::cout << (numberOfTrees - totalChosen) << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int testCases;
    std::cin >> testCases;
    while (testCases--) {
        processTestCase();
    }

    return 0;
}
