#include <algorithm>
#include <cmath>
#include <iostream>
#include "library.h"
#include <map>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>
#include <climits>

using namespace std;
using namespace library;

class Problem {
  int mat[100][100];
  int N;

  public:

  // structure for information of each cell
  struct cell
  {
    int x, y;
    int distance;
    cell(int x, int y, int distance) :
      x(x), y(y), distance(distance) {}
  };

  // Utility method for comparing two cells
  friend bool operator<(const Problem::cell& a, const Problem::cell& b)
  {
    if (a.distance == b.distance)
    {
      if (a.x != b.x)
        return (a.x < b.x);
      else
        return (a.y < b.y);
    }
    return (a.distance < b.distance);
  }

  // Utility method to check whether a point is
  // inside the grid or not
  bool isInsideGrid(int i, int j)
  {
    return (i >= 0 && i < 500 && j >= 0 && j < 500);
  }

  // Method returns minimum cost to reach bottom
  // right from top left
  int shortest(int grid[500][500], int row, int col)
  {
    int dis[row][col];

    // initializing distance array by INT_MAX
    for (int i = 0; i < row; i++)
      for (int j = 0; j < col; j++)
        dis[i][j] = INT_MAX;

    // direction arrays for simplification of getting
    // neighbour
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};

    set<cell> st;

    // insert (0, 0) cell with 0 distance
    st.insert(cell(0, 0, 0));

    // initialize distance of (0, 0) with its grid value
    dis[0][0] = grid[0][0];

    // loop for standard dijkstra's algorithm
    while (!st.empty())
    {
      // get the cell with minimum distance and delete
      // it from the set
      cell k = *st.begin();
      st.erase(st.begin());

      // looping through all neighbours
      for (int i = 0; i < 4; i++)
      {
        int x = k.x + dx[i];
        int y = k.y + dy[i];

        // if not inside boundary, ignore them
        if (!isInsideGrid(x, y))
          continue;

        // If distance from current cell is smaller, then
        // update distance of neighbour cell
        if (dis[x][y] > dis[k.x][k.y] + grid[x][y])
        {
          // If cell is already there in set, then
          // remove its previous entry
          if (dis[x][y] != INT_MAX)
            st.erase(st.find(cell(x, y, dis[x][y])));

          // update the distance and insert new updated
          // cell in set
          dis[x][y] = dis[k.x][k.y] + grid[x][y];
          st.insert(cell(x, y, dis[x][y]));
        }
      }
    }

    // uncomment below code to print distance
    // of each cell from (0, 0)
    /*
       for (int i = 0; i < row; i++, cout << endl)
       for (int j = 0; j < col; j++)
       cout << dis[i][j] << " ";
       */
    // dis[row - 1][col - 1] will represent final
    // distance of bottom right cell from top left cell
    return dis[row - 1][col - 1];
  }


    void readInput() {
      N=0;
      string line;

      while(!cin.eof()) {
        getline(cin, line);
        if(line.empty()) continue;
        for(int i=0;i<line.size();i++) {
          mat[N][i] = line[i]-'0';
        }
        N++;
      }
    }

    int getVal(int i, int j) {
      int itile = i / N;
      int jtile = j / N;
      int val = (mat[i%N][j%N] + itile + jtile);
      return ((val - 1) % 9 )+1;
    }

    long solve1() {
      int best[500][500];
      best[0][0]=0;
      for(int i=0;i<5*N;i++) {
        for(int j=0;j<5*N;j++) {
          if(i==0 && j==0) continue;
          if(i==0) best[i][j]=best[i][j-1]+getVal(i,j);
          else if(j==0) best[i][j]=best[i-1][j]+getVal(i,j);
          else best[i][j]=min(best[i-1][j], best[i][j-1])+getVal(i,j);
        }
      }

      for(int i=0;i<5*N;i++) {
        for(int j=0;j<5*N;j++) {
          //cout << best[i][j] << " ";
          best[i][j] = getVal(i,j);

        }
        cout << "\n";
      }

      return shortest(best, 500,500);
    }

    long solve() {
      int best[N][N];
      best[0][0]=0;
      for(int i=0;i<N;i++) {
        for(int j=0;j<N;j++) {
          if(i==0 && j==0) continue;
          if(i==0) best[i][j]=best[i][j-1]+mat[i][j];
          else if(j==0) best[i][j]=best[i-1][j]+mat[i][j];
          else best[i][j]=min(best[i-1][j], best[i][j-1])+mat[i][j];
        }
      }
      for(int i=0;i<N;i++) {
        for(int j=0;j<N;j++) {
          cout << best[i][j] << " ";
        }
        cout << "\n";
      }
      return best[N-1][N-1];
    }

};

int main() {
  Problem p;
  p.readInput();
  cout << p.solve1() << "\n";
}
