#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <cmath>
#include <stack>
#include "library.h"

using namespace std;
using namespace library;

class Problem {

  public:
    int points(char in) {
      if(in == ')') return 3 ;
      if(in == ']') return 57 ;
      if(in == '}') return 1197 ;
      if(in == '>') return 25137 ;
      return 0;
    }
    int points2(char in) {
      if(in == ')') return 1 ;
      if(in == ']') return 2 ;
      if(in == '}') return 3 ;
      if(in == '>') return 4 ;
      return 0;
    }
    char matchingCloser(char cur) {
        if(cur == '(') return ')';
        else if(cur == '{') return '}';
        else if(cur == '[') return ']';
        else if(cur == '<') return '>';
        return 0;
    }
    char matchingOpener(char cur) {
        if(cur == ')') return '(';
        else if(cur == '}') return '{';
        else if(cur == ']') return '[';
        else if(cur == '>') return '<';
    }
    int errorPos(string s, char & actual, char & expected, long & score) {
      stack<char> st;
      for(int i=0; i<s.size(); i++) {
        char cur=s[i];
        if(cur == '(' || cur == '[' || cur == '{' || cur == '<') st.push(cur);
        else {
          if(st.empty() || cur != matchingCloser(st.top())) {
            actual = cur;
            if(!st.empty()) expected = matchingCloser(st.top());
            return i;
          } else st.pop();
        }
      }
      score = 0;
      while(!st.empty()) {
        score *= 5;
        score+=points2(matchingCloser(st.top()));
        st.pop();
      }
      return -1;
    }
    void readInput() {
      vector<string> lines;
      long p=0;
      vector<long> scoo;
      while(!cin.eof()) {
        string line;
        getline(cin, line);
        if(!cin.eof()) lines.push_back(line);
        char actual, expected;
        long score;
        int errorpos = errorPos(line, actual, expected, score);
        if(errorpos != -1) {
          p+=points(actual);
          cout << line << " expected " << expected << " but got "<<actual<< "\n";
        } else {
          scoo.push_back(score);
        }
      }
      sort(scoo.begin(), scoo.end());
      cout << scoo[scoo.size()/2] << "\n";

      
    }

    long solve() {
      return 0;
    }

};

int main() {
  Problem p;
  p.readInput();
}
