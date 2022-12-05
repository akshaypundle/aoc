#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>
#include <climits>
#include "projecteuler/solutions/library.h"

using namespace std;
using namespace library;

class Problem {

  public:  

   vector<string> lines;
    void readInput() {
      string line;

      while(!cin.eof()) {
        getline(cin, line);
        lines.push_back(line);
      }
    }

    long solve() {
      int max=0;
      int cur=0;
      vector<int> cals;
      for(string line:lines) {
        if(!line.empty()) {
          cur+=stoi(line);
        } else {
          if(cur > max) {
            max=cur;
          }
          cals.push_back(cur);
          cur=0;
        }

        if(cur > max) max = cur;
      }
      sort(cals.begin(), cals.end(), greater<int>());
      return cals[0]+cals[1]+cals[2];
    }

};

int main() {
  Problem p;
  p.readInput();
  cout << p.solve() << "\n";
}
