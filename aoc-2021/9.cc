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
    int mat[100][100];
    int N=0;

    void readInput() {
      string line;
      while(!cin.eof()) {
        getline(cin, line);
        if(cin.eof()) break;
        for(int i=0;i<line.size();i++) {
          mat[N][i]=line[i]-'0';
        }
        N++;
      }
    }

    int getSafe(int i, int j) {
      if(i<0 || j <0 || i>=N || j>=N) return 10;
      return mat[i][j];
    }


    bool isLow(int i, int j) {
      return mat[i][j] < getSafe(i-1,j) &&
        mat[i][j] < getSafe(i+1,j) &&
        mat[i][j] < getSafe(i,j-1) &&
        mat[i][j] < getSafe(i,j+1);
    }


    void floodfill(int i, int j, int k) {
      if(i < 0 || j < 0 || i>=N || j >=N || mat[i][j]==9 || mat[i][j]==k) {
        return;
      }
      mat[i][j]=k;
      floodfill(i-1,j,k);
      floodfill(i+1,j,k);
      floodfill(i,j-1,k);
      floodfill(i,j+1,k);

    }

    long solve() {
      int n=11;
      for(int i=0;i<N;i++) {
        for(int j=0;j<N;j++) {
          if(mat[i][j] < 9) {
            floodfill(i,j,n);
            n++;
          }
        }
      }
      int c[n]={0};

      for(int i=0;i<N;i++) {
        for(int j=0;j<N;j++) {
          if(mat[i][j] > 10) {
            c[mat[i][j]]++;
          }
        }
      }

      sort(c, c + n);
      return c[n-1]*c[n-2]*c[n-3];
      /*
      int count = 0;
      for(int i=0;i<N;i++) {
        for(int j=0;j<N;j++) {
          if(isLow(i,j)) 
            count+=mat[i][j]+1;
        }
      }
      return count;
      */


    }

};

int main() {
  Problem p;
  p.readInput();
  cout << p.solve() << "\n";
}
