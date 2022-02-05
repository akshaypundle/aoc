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
  public:
    string algoString;
    string flippedalgo;
    set<pair<int,int>> points;
    int MAXX;
    int MAXY;
    int MINX;
    int MINY;
    int presentPixel=1;
    int absentPixel=0;


    void setpoints(set<pair<int,int>> p) {
      int mx=0,my=0;
      int minx=99999999, miny = 99999999;
      for(auto pt : p)  {
        if(pt.first > mx) mx=pt.first;
        if(pt.second > my) my=pt.second;
        if(pt.first < minx) minx=pt.first;
        if(pt.second < miny) miny=pt.second;
      }
      MAXX=mx+2;
      MAXY=my+2;
      MINX=minx-2;
      MINY=miny-2;
      points = p;
    }

    void readInput() {
      string line;
      getline(cin, line);

      algoString = line;
      flippedalgo=line;
      for(int i=0;i<line.size();i++) {
        if(flippedalgo[i] == '#') flippedalgo[i]='.';
        else flippedalgo[i]='#';
      }

      set<pair<int,int>> pts;
      int j=0;
      while(!cin.eof()) {
        getline(cin, line);
        if(line.empty()) continue;
        for(int i=0;i<line.size();i++) {
          if(line[i] == '#') pts.insert(make_pair(i,j));
        }
        j++;
      }
      setpoints(pts);
    }

    int pixel(int x, int y) {
      if(points.find(make_pair(x,y)) != points.end()) {
        return presentPixel;
      }
      return absentPixel;
    }

    void enhance() {
      set<pair<int,int>> newpoints;
      for(int i=MINX;i<MAXX;i++) {
        for(int j=MINY;j<MAXY;j++) {
          int n = pixel(i-1,j-1)*256+
            pixel(i,j-1)*128 +
            pixel(i+1,j-1)*64+
            pixel(i-1,j)*32+
            pixel(i,j)*16+
            pixel(i+1,j)*8+
            pixel(i-1,j+1)*4+
            pixel(i,j+1)*2 +
            pixel(i+1,j+1)*1;
          if(algoString[n] == '#') newpoints.insert(make_pair(i,j));

        }
      }
      setpoints(newpoints);
    }

    void draw() {
      cout << "\n";
      for(int j=MINY;j<MAXY;j++) {
        for(int i=MINX;i<MAXX;i++) {
          if(pixel(i,j) == 1) cout << "#";
          else cout << '.';
        }
        cout << "\n";
      }
      cout << "\n";
    }

    long solve() {

      draw();

      for(int i=0;i<25;i++) {
        string s = algoString;
        algoString = flippedalgo;
        enhance();
        draw();

        presentPixel=0;
        absentPixel=1;
        algoString=s;

        enhance();
        draw();

        presentPixel=1;
        absentPixel=0;
      }

        return points.size();
    }

};

int main() {
  Problem p;
  p.readInput();
  cout << p.solve() << "\n";
}
