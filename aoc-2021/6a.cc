#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <cmath>

using namespace std;

class Problem {
  public:
    vector<int> lf {1,  4, 2, 4, 5, 3, 5, 2, 2, 5, 2, 1, 2, 4, 5, 2, 3, 5, 4, 3, 3, 1, 2, 3,
      2, 1, 4, 4, 2, 1, 1, 4, 1, 4, 4, 4, 1, 4, 2, 4, 3, 3, 3, 3, 1, 1, 5, 4,
      2, 5, 2, 4, 2, 2, 3, 1, 2, 5, 2, 4, 1, 5, 3, 5, 1, 4, 5, 3, 1, 4, 5, 2,
      4, 5, 3, 1, 2, 5, 1, 2, 2, 1, 5, 5, 1, 1, 1, 4, 2, 5, 4, 3, 3, 1, 3, 4,
      1, 1, 2, 2, 2, 5, 4, 4, 3, 2, 1, 1, 1, 1, 2, 5, 1, 3, 2, 1, 4, 4, 2, 1,
      4, 5, 2, 5, 5, 3, 3, 1, 3, 2, 2, 3, 4, 1, 3, 1, 5, 4, 2, 5, 2, 4, 1, 5,
      1, 4, 5, 1, 2, 4, 4, 1, 4, 1, 4, 4, 2, 2, 5, 4, 1, 3, 1, 3, 3, 1, 5, 1,
      5, 5, 5, 1, 3, 1, 2, 1, 4, 5, 4, 4, 1, 3, 3, 1, 4, 1, 2, 1, 3, 2, 1, 5,
      5, 3, 3, 1, 3, 5, 1, 5, 3, 5, 3, 1, 1, 1, 1, 4, 4, 3, 5, 5, 1, 1, 2, 2,
      5, 5, 3, 2, 5, 2, 3, 4, 4, 1, 1, 2, 2, 4, 3, 5, 5, 1, 1, 5, 4, 3, 1, 3,
      1, 2, 4, 4, 4, 4, 1, 4, 3, 4, 1, 3, 5, 5, 5, 1, 3, 5, 4, 3, 1, 3, 5, 4,
      4, 3, 4, 2, 1, 1, 3, 1, 1, 2, 4, 1, 4, 1, 1, 1, 5, 5, 1, 3, 4, 1, 1, 5,
      4, 4, 2, 2, 1, 3, 4, 4, 2, 2, 2, 3};
    void readInput() {
      string line;
      getline(cin,   line);

      while(!cin.eof()) {
        getline(cin,   line);
      }
    }

    long solve() {
      long counts[9]={0};
      for(int i=0;i<lf.size();i++) {
        counts[lf[i]]++;
      }
      for(int i=0;i<256;i++) {
        long next[9]={0};

        for(int j=1;j<9;j++) {
          next[j-1]+=counts[j];
        }
        next[6]+=counts[0];
        next[8]=counts[0];

        for(int j=0;j<9;j++) {
          counts[j]= next[j];
        }
      }
      long c=0;
      for(int j=0;j<9;j++) {
        c+=counts[j];
      }

      return c;
    }

};

int main() {
  Problem p;
  //p.readInput();
  cout << p.solve() << "\n";
}
