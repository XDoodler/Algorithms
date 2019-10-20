/*
   author : nuttela
*/
#include<bits/stdc++.h>

using namespace std;

int main() {
  // freopen("i3.txt", "w", stdout);

  srand(time(NULL));

  std::random_device rd;
  std::mt19937 eng(rd());
  std::uniform_int_distribution < > distr(1, 100);
  //static const char generator[] = "abcdefghijklmnopqrstuvwxyz";
  //static const char leet[] = "12";

  //TEST CASES SET BY USER
  int tc = 1;

  cout << tc << '\n';

  while (tc--) {

    // MAXIMUM NODES OF TREE
    const int maxN = 10;
    const int N = rand() % maxN + 1;

    //PRINT NODES OF TREE
    cout << N << endl;

    //EDGES
    int x = 10, y = 10;

    //VALUES OF NODES (IF TO BE PROVIDED)
    for (int i = 0; i < N; ++i) {
      cout << x + rand() % ((y + 1) - (x)) << ' ';
    }
    cout << endl;

    //BASE TREE TEST DATA STARTS
    vector < int > nodeIds;
    for (int i = 1; i <= N; i++) {
      nodeIds.push_back(i);
    }
    random_shuffle(nodeIds.begin(), nodeIds.end());

    vector < int > usedNodeIds = {
      nodeIds.back()
    };
    nodeIds.pop_back();

    for (int i = 0; i < N - 1; i++) {
      const int newNodeId = nodeIds.back();
      const int oldNodeId = usedNodeIds[rand() % usedNodeIds.size()];

      cout << newNodeId << " " << oldNodeId << endl;

      usedNodeIds.push_back(newNodeId);
      nodeIds.pop_back();
    }
    //BASE TREE TEST DATA ENDS      
  }
}
