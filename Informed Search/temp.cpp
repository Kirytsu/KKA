#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector <int>> GOAL_STATE = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 0}
};

vector<vector <int>> START_STATE = {
    {2, 3, 5}, 
    {6, 1, 4},
    {8, 7, 0}
};

// Atas, kanan, bawah , kiri
vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

struct PuzzleState {
    vector<vector<int>> state;
    int x, y; // position of the blank (0)
    int cost;

    // Constructor
    PuzzleState(const vector<vector<int>>& s, int blankX, int blankY, int heuristicCost) {
        state = s;
        x = blankX;
        y = blankY;
        cost = heuristicCost;
    }

    // Comparator for the priority queue based on heuristic (cost)
    bool operator<(const PuzzleState& other) const {
        return cost > other.cost; // lower cost is higher priority
    }
};

// Heuristic function: number of misplaced cells
int heuristic(const vector<vector<int>>& curState){
    int h = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (curState[i][j] != 0 && curState[i][j] != GOAL_STATE[i][j]) {
                h++;
            }
        }
    }
    return h;
}

// Greedy BFS algorithm
int greedyBFS(int startX, int startY, const vector<vector<int>>& curState) {
    priority_queue<PuzzleState> pq;

    // Push the initial state
    pq.push(PuzzleState(curState, startX, startY, heuristic(curState)));

    int steps = 0;

    while (!pq.empty()) {
        steps++;
        PuzzleState current = pq.top();
        pq.pop();

        // Check if it's the goal state
        if (current.state == GOAL_STATE) {
            cout << "Goal state reached in " << steps << " steps!" << endl;
            return steps;
        }

        // Generate new states by moving the blank tile
        for (auto dir : directions) {
            int newX = current.x + dir.first;
            int newY = current.y + dir.second;

            // Check if the new position is within bounds
            if (newX >= 0 && newX < 3 && newY >= 0 && newY < 3) {
                // Create a new state by swapping the blank tile
                vector<vector<int>> newState = current.state;
                swap(newState[current.x][current.y], newState[newX][newY]);

                // Push the new state with its heuristic into the priority queue
                pq.push(PuzzleState(newState, newX, newY, heuristic(newState)));
            }
        }
    }

    return -1; // No solution found
}

int main() {
    int x, y;

    // Find the position of the blank (0) in the START_STATE
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (START_STATE[i][j] == 0) {
                x = i;
                y = j;
            }
        }
    }

    // Call the greedy BFS function
    int result = greedyBFS(x, y, START_STATE);

    if (result != -1) {
        cout << "Solved in " << result << " steps." << endl;
    } else {
        cout << "No solution found." << endl;
    }

    return 0;
}
