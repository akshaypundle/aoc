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
// A rock
// B paper
// C scissors
//
// X rock
// Y paper
// Z scissors
//
//
// X def C
// Z def B
// Y def A
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
      int score  = 0  ;
      for(string line:lines) {
        if(line.empty()) continue;

        score += (line[2] - 'X' + 1);
        if(line == "A X" || line == "B Y" || line == "C Z") {
          score += 3;
        } else if( line == "C X" || line == "B Z" || line == "A Y") {
          score += 6;
        }
      }      
      return score;
    }
// A rock
// B paper
// C scissors
//
// X rock
// Y paper
// Z scissors
//
    long solve2() {
      int score  = 0  ;
      for(string line:lines) {
        if(line.empty()) continue;
        if(line == "A X") {
          score += 3;
        } else if (line == "A Y") {
          score += 4;
        }else if (line == "A Z") {
          score += 8;
        }else if (line == "B X") {
          score += 1;
        }else if (line == "B Y") {
          score += 5;
        }else if (line == "B Z") {
          score += 9;
        }else if (line == "C X") {
          score += 2;
        }else if (line == "C Y") {
          score += 6;
        }else if (line == "C Z") {
          score += 7;
        }
      }      
      return score;
    }

};

int main() {
  Problem p;
  p.readInput();
  cout << p.solve2() << "\n";
}
