#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <cmath>
#include "library.h"
#include <stack>

using namespace std;
using namespace library;

class Problem {
  public:
    int nextNodeIndex;
    map<string, vector<string>> nodes;
    void readInput() {
      nextNodeIndex = 0;
      string line;

      while(!cin.eof()) {
        getline(cin, line);
        if(!cin.eof()) {
          vector<string> nn = Split(line, '-');
          if(nodes.find(nn[0]) == nodes.end()) {
            nodes[nn[0]]= vector<string>();
          }

          if(nodes.find(nn[1]) == nodes.end()) {
            nodes[nn[1]]= vector<string>();
          }
          nodes[nn[0]].push_back(nn[1]);
          nodes[nn[1]].push_back(nn[0]);
        }
      }

      for(auto it = nodes.begin();it!=nodes.end();++it) {
        cout << it->first << " --- " << " ";
        for(string s : it->second) {
          cout << s << " ";
        }
        cout << "\n";
      }
    }

    map<string, int> visited;
    int times;

    bool canVisit(string s) {
      if(s[0] >= 'A' && s[0]<='Z') return true;
      if(visited.find(s)==visited.end() || visited[s]==0) return true;
      if(visited[s] == 2) return false;
      if(visited[s] == 1) {
        for(auto it = visited.begin();it!=visited.end();++it) {
          if(it->second == 2) return false;
        }
      }
      return true;
    }

    void visit(string s) {
      if(s == "end") {
        times++;
        return;
      } else if(!canVisit(s)) {
        return;
      }
      if(s[0] >= 'a' && s[0]<='z') {
         if(visited.find(s)==visited.end()) visited[s]=1;
         else visited[s]++;
      }


      for(auto child : nodes[s]) {
        if(child == "start") continue;

        if(child[0] >= 'a' && child[0]<='z') {
          if(canVisit(child))  {
            visit(child);
            if(visited.find(child)!=visited.end()) visited[child]--; 
          }
        } else if(child[0] >= 'A' && child[0]<='Z') {
          visit(child);
        }
        //if(times > 100) exit(-1);
      }
    }

    long solve() {
      visit("start");

      return times;
    }



};

int main() {
  Problem p;
  p.readInput();
  cout << p.solve() << "\n";
}
