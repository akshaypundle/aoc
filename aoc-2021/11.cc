#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <cmath>
#include "library.h"

using namespace std;
using namespace library;

class Problem {
  public:
    vector<int> seen;
    int mat[10][10];
    void readInput() {
      string line;
      for(int i=0;i<10;i++) {
        getline(cin, line);
        for(int j=0;j<10;j++) {
          mat[i][j] = line[j]-'0';
        }
      }
      print();
    }

    void addSeen(int i,int j) {
      seen.push_back(i+100*j);
    }

    bool hasSeen(int i,int j) {
      return find(seen.begin(), seen.end(), i+100*j) != seen.end();
    }


    int step() {
      for(int i=0;i<10;i++) {
        for(int j=0;j<10;j++) {
          mat[i][j]++;
        }
      }

      cout << "111111111111"<<"\n";;
      print();

      for(int i=0;i<10;i++) {
        for(int j=0;j<10;j++) {
          if(!hasSeen(i,j) && mat[i][j] > 9) {
            addSeen(i,j);
            flash(i-1,j-1);
            flash(i-1,j);
            flash(i-1,j+1);
            flash(i,j-1);
            flash(i,j+1);
            flash(i+1,j-1);
            flash(i+1,j);
            flash(i+1,j+1);
          }
        }
      }

      int f=0;
      for(int i=0;i<10;i++) {
        for(int j=0;j<10;j++) {
          if(mat[i][j] >9) {
            f++;
            mat[i][j]=0;
          }
        }
      }

      seen.clear();

      return f;

    }


    void flash(int i, int j) {
      if(i<0 || j<0 || i>9 || j>9 || hasSeen(i,j) || mat[i][j] > 9 ) {
        return;
      }
      else mat[i][j]++;
      if(mat[i][j] == 10) {
        addSeen(i,j);
        flash(i-1,j-1);
        flash(i-1,j);
        flash(i-1,j+1);
        flash(i,j-1);
        flash(i,j+1);
        flash(i+1,j-1);
        flash(i+1,j);
        flash(i+1,j+1);
      }
    }

    void print() {
      for(int i=0;i<10;i++) {
        for(int j=0;j<10;j++) {
          cout << mat[i][j];
        }
        cout << "\n";
      }
      cout << "\n";
    }


    long solve() {
      for(int i=0;i<10000;i++) {
        int f = step();
        if(f == 100) {
          cout << i+1 << "\n";
          return 0;
        }
    
        //cout << "after step "<< i+1 << "\n";
        //print();
      }
      return 0;
    }

};

int main() {
  Problem p;
  p.readInput();
  cout << p.solve() << "\n";
}
