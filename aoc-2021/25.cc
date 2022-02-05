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

using namespace std;
using namespace library;

class Problem {
  vector<vector<char>> input;
  int rows,cols;

  public:
    void print(vector<vector<char>>& c) {
      for(auto v : c) {
        for(auto ch:v) {
          cout << ch;
        }
        cout <<"\n";
      }
      cout <<"\n";
    }

    int wrapIt(int i, int limit) {
      if(i >= limit ) return i-limit;
      return i;
    }

    tuple<int,int> nextPos(int i, int j, char ch) {

      if(ch == '>') {
        return make_tuple(i, wrapIt(j+1, cols));
      }

      if(ch == 'v') {
        return make_tuple(wrapIt(i+1, rows), j);
      }
      return make_tuple(0,0);
    }


    bool step(vector<vector<char>>& c) {
      bool changed = false;
      auto nv = c;
      for(int i=0;i<rows;i++) {
        for(int j=0;j<cols;j++) {
          if(c[i][j] == '>') {
            const auto nxt = nextPos(i,j, c[i][j]);
            if(c[get<0>(nxt)][get<1>(nxt)] == '.') {
              nv[get<0>(nxt)][get<1>(nxt)] = c[i][j];
              nv[i][j]='.';
              changed = true;
            }
          }
        }
      }


      c=nv;

      for(int i=0;i<rows;i++) {
        for(int j=0;j<cols;j++) {
          if(c[i][j] == 'v') {
            const auto nxt = nextPos(i,j, c[i][j]);
            if(c[get<0>(nxt)][get<1>(nxt)] == '.') {
              nv[get<0>(nxt)][get<1>(nxt)] = c[i][j];
              nv[i][j]='.';
              changed = true;
            }
          }
        }
      }

      c=nv;
      return changed;
    }


    void readInput() {
      string line;
      while(!cin.eof()) {
        getline(cin, line);
        if(line.empty()) break;
        input.emplace_back();
        for(char ch : line) {
          input.back().emplace_back(ch);
        }
      }
      rows = input.size();
      cols = input[0].size();
      print(input);
    }

    long solve() {
      for(int i=1;i<10000;i++) {
        cout << "step "<<i<<"\n";
        bool changed= step(input);
        print(input);
        if(!changed) break;
      }
      return 0;
    }

};

int main() {
  Problem p;
  p.readInput();
  cout << p.solve() << "\n";
}
