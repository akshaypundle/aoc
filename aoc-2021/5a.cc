#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <cmath>

using namespace std;

class Problem {
  int mat[1000][1000];
  public:
    void readInput() {
      for(int i=0;i<1000;i++) {
        for(int j=0;j<1000;j++) {
          mat[i][j]=0;
        }
      }
      string line;
      char ch;
      int x1,y1,x2,y2;
      while(!cin.eof()) {
        cin >> x1 ;
        if(cin.eof()) break;
        cin >> ch;
        cin >> y1 ;
        cin >> ch >> ch;
        cin >> x2 >> ch >> y2;


        if(x1 == x2) {
          for(int ty = min(y1, y2); ty <=max(y1,y2); ty++) {
            mat[x1][ty]++;
          }
        } else if(y1 == y2) {
          for(int tx = min(x1, x2); tx <=max(x1,x2); tx++) {
            mat[tx][y1]++;
          }
        } else if( max(x1,x2) - min(x1,x2) == max(y2,y1) - min(y1,y2)) {
          int sx = x1 < x2 ? 1 : -1;
          int sy = y1 < y2 ? 1 : -1;
          for(int tx = 0;tx <=max(x1,x2) - min(x1,x2); tx++) {
            mat[x1 + sx*tx][y1 + sy*tx]++;
          }
        }
      }

    }

    long solve() {
      int c=0;
      for(int j=0;j<1000;j++) {
      for(int i=0;i<1000;i++) {
          if(mat[i][j]>=2) c++;
          if(mat[i][j] == 0) cout << ".";
          else cout << mat[i][j];
        }
        cout << "\n";
      }
      return c;
    }

};

int main() {
  Problem p;
  p.readInput();
  cout << p.solve() << "\n";
}
