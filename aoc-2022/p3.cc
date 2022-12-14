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
        if(!line.empty()) lines.push_back(line);
      }
    }

    int prioChar(char c) {
      if(c >= 'a' && c<='z')  {
        return c-'a'+1;
      }
      return c-'A'+27;
    }

    long findPrio(string line) {
      long p =0;
      string l1= line.substr(0,line.length()/2);
      string l2= line.substr(line.length()/2, line.length()/2);

      set<char> occurrs;
      for(char c : l1) {
        occurrs.insert(c);
      }
      
      for(char c : l2) {
        if(occurrs.find(c) != occurrs.end()) {
          cout << c << "\n";
          p+= prioChar(c);
          occurrs.erase(c);
        }
      }

      return p;

    }

    long solve() {
      long pri = 0;
      for(string line:lines) {
        if(line.empty()) continue;
        pri+=findPrio(line);
      }
      return pri;
    }

    int findCommon(string l1, string l2, string l3) {
      set<char> o1,o2,o3;
      for(char c : l1) {
        o1.insert(c);
      }
      for(char c : l2) {
        if(o1.find(c) != o1.end()) {
          o2.insert(c);
        }
      }
      for(char c : l3) {
        if(o2.find(c) != o2.end()) {
          o3.insert(c);
        }
      }

      cout << o3.size() << "\n";
      if(o3.size() > 1 || o3.empty()) {
        throw std::invalid_argument("fuck me");
      }
      return prioChar(*o3.begin());
    }

    long solve2() {
      long pri = 0;
      int n=lines.size()/3;
      cout << lines.size()<< " "<<n<<"\n";

      for(int i=0;i<n;i++) {
        pri+=findCommon(lines[3*i],lines[3*i+1],lines[3*i+2]);
      }
      return pri;
    }
};

int main() {
  Problem p;
  p.readInput();
  cout << p.solve2() << "\n";
}
