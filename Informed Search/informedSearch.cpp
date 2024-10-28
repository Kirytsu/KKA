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

vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
struct PuzzleState {
    vector<vector <int>> state;
    int x, y;
    int cost;

    // cek operator udh bener blm prioritynya
    bool operator<(const PuzzleState& state) const {
        return cost > state.cost;
    }
};

// Heuristic function : number of misplaced cells
int heuristic(vector<vector<int>> curState){
    int h=0;
    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){
            if ((curState[i][j] != GOAL_STATE[i][j]) && curState[i][j] != 0)
            h++;
        }
    }
    return h;
}

int greedyBFS(int x, int y){
    int lowestHeuristic=10;
    int steps=0;
    priority_queue <PuzzleState> pq;
    pq.push(PuzzleState(START_STATE, x, y, heuristic(START_STATE)));
    while (1){
        steps++;
        

        if (lowestHeuristic==0){
            return steps;
        }
    }
}

int aStar(){

}
int main(){
    int x, y;
    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){
            if (START_STATE[i][j] == 0){
                x = i; y = j;
            }
        }
    }
    // greedyBFS();
    return 0;
}