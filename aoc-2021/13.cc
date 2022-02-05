#include <utility>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <cmath>
#include <sstream>
#include "library.h"

using namespace std;
using namespace library;

class Problem {
  public:
    vector<pair<int,int>> points;
    vector<pair<char,int>> folds;
    void readInput() {
      string line;

      while(true) {
        int x,y;
        char ch;
        getline(cin, line);
        if(line.size() == 0) break;
        stringstream ss(line);
        ss >> x >> ch >> y;
        points.push_back(make_pair(x,y));
      }



      while(!cin.eof()) {
        string fold, along;
        char xory;
        char eq;
        int val;
        getline(cin, line);
        if(line.size() == 0) break;
        stringstream ss(line);
        ss >> fold >> along >> xory >> eq >> val;
        folds.push_back(make_pair(xory, val));

      }
    }

    pair<int,int> foldOne(pair<char,int> fold, pair<int,int> point) {
      pair<int,int> newPoint(point);
      //cout << "folding "<<newPoint.first << "," << newPoint.second << "\n";
      if(fold.first == 'x') {
        if(point.first > fold.second) {
          newPoint.first = 2*fold.second - point.first;
        } 
      } else if(fold.first == 'y') {
        if(point.second > fold.second) {
          newPoint.second = 2*fold.second - point.second;
        } 
      }
      return newPoint;
    }

    long solve() {
      int maxx=0,maxy=0;
      set<pair<int,int>> news;
        for(auto p : points) {
          pair<int,int> folded(p);
          for(auto fold : folds) {
            folded = foldOne(fold, folded);
          //cout << p.first<<","<<p.second << "   ---> " << folded.first<<","<<folded.second << "\n";;
          }
          news.insert(folded);
      }

      for(auto p:news) {
        if(maxx < p.first) maxx = p.first;
        if(maxy < p.second) maxy = p.second;
      }

      for(int i=0;i<=maxy;i++) {
        for(int j=0;j<=maxx;j++) {
          if(news.find(make_pair(j,i)) != news.end()) cout << "#"; 
          else cout << ".";
        }
        cout << "\n";
      }
      return news.size();
    }

};

int main() {
  Problem p;
  p.readInput();
  cout << p.solve() << "\n";
}
