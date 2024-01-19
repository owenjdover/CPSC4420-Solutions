/*
Author: Owen Dover
01/19/2024
Program to solve 8 Puzzle Problem using BFS
*/

#include<iostream>
#include<vector>
#include<map>
#include<queue>
using namespace std;

typedef vector<vector<char>> state; // 3x3 matrix representing a state of the puzzle

map<state, bool> visited;         // visited states
map<state, state> pred;           // predecessor state we came from
map<state, int> dist;             // distance from source node
map<state, vector<state>> nbrs;   // neighbor states of a certain state

// generates vector of neighbor states from given state, then adds vector to nbrs dict
void findNeighbors(const state thisState){
    vector<state>neighbors;
    // find blank tile index in given state
    int blankRow, blankCol;
    for(int i = 0; i < 3; i++){
        for(int v = 0; v < 3; v++){
            if (thisState[i][v] == ' '){
                blankRow = i;
                blankCol = v;
                break;
            }
        }
    }

    //4 possible actions can be taken from a given state

    //move blank tile up
    if(blankRow-1 >= 0){
        state tempState = thisState;
        swap(tempState[blankRow][blankCol], tempState[blankRow-1][blankCol]);
        neighbors.push_back(tempState);
    }
    //move blank tile down
    if(blankRow+1 < 3){
        state tempState = thisState;
        swap(tempState[blankRow][blankCol], tempState[blankRow+1][blankCol]);
        neighbors.push_back(tempState);
    }
    //move blank tile left
    if(blankCol - 1 >= 0){
        state tempState = thisState;
        swap(tempState[blankRow][blankCol], tempState[blankRow][blankCol-1]);
        neighbors.push_back(tempState);
    }
    //move blank tile right
    if(blankCol+1 < 3){
        state tempState = thisState;
        swap(tempState[blankRow][blankCol], tempState[blankRow][blankCol+1]);
        neighbors.push_back(tempState);
    }
    nbrs[thisState] = neighbors;
return;
}


// BFS, gradually expands graph, once graph has been traversed returns number of states in graph
int search(state source_node)
{
  queue<state> to_visit;
  to_visit.push(source_node);
  visited[source_node] = true;
  dist[source_node] = 0;
  int numStates = 1;
  
  while (!to_visit.empty()) {
    state curnode = to_visit.front();
    to_visit.pop();
    findNeighbors(curnode);
    for (state n : nbrs[curnode])
      if (!visited[n]) {
        numStates++;
	pred[n] = curnode;
	dist[n] = 1 + dist[curnode];
	visited[n] = true;
	to_visit.push(n);
      }
  }
  return numStates;
}

int main(){
    
    const state begin = {
        {'5', '4', '8'},
        {'1', ' ', '3'},
        {'6', '2', '7'}
    };
    const state end = {
        {' ', '1', '2'},
        {'3', '4', '5'},
        {'6', '7', '8'}
    };

    int numStates = search(begin);
    cout << "Number of possible states: " << numStates << endl;
    if(visited[end])
        cout << "Target can be reached from source node. Distance from source node: " << dist[end] << endl;
    else
        cout << "Impossible to reach target from source node." << endl;
    return 0;
}

