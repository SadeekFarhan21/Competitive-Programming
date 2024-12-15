#include <bits/stdc++.h>
using namespace std;

// Struct for direction mapping and helper operations
struct GridHelper {
    static const int dr[4];
    static const int dc[4];
    
    static int directionIndex(char c) {
        switch (c) {
            case 'L': return 0;
            case 'R': return 1;
            case 'U': return 2;
            case 'D': return 3;
            default: return -1;
        }
    }

    static bool isInside(int r, int c, int N) {
        return (0 <= r && r < N && 0 <= c && c < N);
    }
};

const int GridHelper::dr[4] = {0, 0, -1, 1};
const int GridHelper::dc[4] = {-1, 1, 0, 0};

// Struct to handle the grid and all related operations
struct Grid {
    int N;
    vector<vector<int>> dir;
    vector<vector<bool>> isFixed;
    vector<vector<bool>> escapable;
    vector<vector<int>> outdegEsc;
    queue<pair<int, int>> escapableQueue;
    long long escapableCount;

    Grid(int n) : N(n), escapableCount(0) {
        dir = vector<vector<int>>(N, vector<int>(N, -1));
        isFixed = vector<vector<bool>>(N, vector<bool>(N, false));
        escapable = vector<vector<bool>>(N, vector<bool>(N, false));
        outdegEsc = vector<vector<int>>(N, vector<int>(N, 0));
    }

    void setFixedDirection(int r, int c, char t) {
        dir[r][c] = GridHelper::directionIndex(t);
        isFixed[r][c] = true;
    }

    void initializeEscapable() {
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < N; ++c) {
                if (!isFixed[r][c]) {
                    if (isBoundary(r, c)) {
                        outdegEsc[r][c] = 1;
                        makeEscapable(r, c);
                    }
                } else {
                    int d = dir[r][c];
                    int nr = r + GridHelper::dr[d];
                    int nc = c + GridHelper::dc[d];
                    if (!GridHelper::isInside(nr, nc, N)) {
                        makeEscapable(r, c);
                    }
                }
            }
        }
    }

    void makeEscapable(int r, int c) {
        if (!escapable[r][c]) {
            escapable[r][c] = true;
            escapableCount++;
            escapableQueue.push({r, c});
        }
    }

    void processQueue() {
        while (!escapableQueue.empty()) {
            auto [r, c] = escapableQueue.front();
            escapableQueue.pop();
            updatePredecessors(r, c);
        }
    }

    void updatePredecessors(int r, int c) {
        auto checkPredecessor = [&](int R, int C, int neededDir) {
            if (!GridHelper::isInside(R, C, N)) return;
            if (escapable[R][C]) return;

            if (!isFixed[R][C]) {
                outdegEsc[R][C]++;
                if (outdegEsc[R][C] == 1) {
                    makeEscapable(R, C);
                }
            } else {
                int d = dir[R][C];
                int nr = R + GridHelper::dr[d];
                int nc = C + GridHelper::dc[d];
                if (nr == r && nc == c) {
                    makeEscapable(R, C);
                }
            }
        };

        checkPredecessor(r, c + 1, 0);
        checkPredecessor(r, c - 1, 1);
        checkPredecessor(r + 1, c, 2);
        checkPredecessor(r - 1, c, 3);
    }

    void revertCell(int r, int c) {
        isFixed[r][c] = false;
        dir[r][c] = -1;
        if (!escapable[r][c]) {
            int countDirs = calculateOutdegEsc(r, c);
            outdegEsc[r][c] = countDirs;
            if (countDirs > 0) {
                makeEscapable(r, c);
            }
        }
    }

    int calculateOutdegEsc(int r, int c) {
        int countDirs = 0;
        if (isBoundary(r, c)) countDirs++;
        if (c - 1 >= 0 && escapable[r][c - 1]) countDirs++;
        if (c + 1 < N && escapable[r][c + 1]) countDirs++;
        if (r - 1 >= 0 && escapable[r - 1][c]) countDirs++;
        if (r + 1 < N && escapable[r + 1][c]) countDirs++;
        return countDirs;
    }

    bool isBoundary(int r, int c) {
        return r == 0 || r == N - 1 || c == 0 || c == N - 1;
    }

    long long getUnusableCells() {
        return (long long)N * N - escapableCount;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    Grid grid(N);
    vector<int> rr(Q), cc(Q);
    vector<char> tt(Q);
    for (int i = 0; i < Q; ++i) {
        cin >> rr[i] >> cc[i] >> tt[i];
        rr[i]--;
        cc[i]--;
    }

    for (int i = 0; i < Q; ++i) {
        grid.setFixedDirection(rr[i], cc[i], tt[i]);
    }

    grid.initializeEscapable();
    grid.processQueue();

    vector<long long> answers(Q);
    answers[Q - 1] = grid.getUnusableCells();

    for (int i = Q - 1; i >= 1; --i) {
        grid.revertCell(rr[i], cc[i]);
        grid.processQueue();
        answers[i - 1] = grid.getUnusableCells();
    }

    for (const auto& ans : answers) {
        cout << ans << "\n";
    }

    return 0;
}
