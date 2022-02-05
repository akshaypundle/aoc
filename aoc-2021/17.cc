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

    int xmin,xmax,ymin,ymax;
    map<int,vector<int>> xsolutions;
    map<int,vector<int>> ysolutions;
    set<pair<int,int>> solutions;

    int getXPos(int vx, int step) {
      if(step >= vx+1) return vx*(vx+1)/2;
      return vx*step - (step*(step-1))/2;
    }

    int getYPos(int vy, int step) {
      if(step <= vy+1) {
        return vy*(step) - (step*(step-1))/2;
        
      } else {
        return vy*(vy+1)/2 - ((step - vy - 1)*(step-vy))/2;
      }
    }

    //target area: x=48..70, y=-189..-148
    void readInput() {
      string line;
      getline(cin, line);
      line = line.substr(13);
      stringstream ss(line);
      char ch;
      ss >>ch>>ch>>xmin>>ch>>ch>>xmax>>ch>>ch>>ch>>ymin>>ch>>ch>>ymax;
      //cout << "["<<xmin<<","<<xmax<<"]   ["<<ymin<<","<<ymax<<"]\n";
    }

    void solvex() {
      for(int x=1;x<=xmax;x++) {
        for(int k=1;k<=1000;k++) {
          long p = getXPos(x,k);
          //cout << "x: "<<x<< " k: "<<k<<" xpos "<<p << "\n";
          if(p > xmax) break;
          if(p >= xmin && p <=xmax) {
            if(xsolutions.find(k) == xsolutions.end()) xsolutions[k]=vector<int>();
            xsolutions[k].push_back(x);
          }
        }
      }
    }

    int solvey(int k, vector<int> xs) {
      int maxypos = 0;
      int num=0;
      for(int y=-1000;y<=1000;y++) {
        int p = getYPos(y,k);
        //cout << "y: "<<y<< " k: "<<k<<" ypos "<<p << "\n";
        if(p > ymax) break;
        if(p >= ymin && p <=ymax) {
          int h = y*(y+1)/2;
          if(h > maxypos) maxypos=h;
          num++;
          for(int x:xs) {
            pair<int,int> pai = make_pair(x,y);
            if(solutions.find(pai) == solutions.end()) solutions.insert(pai);
          }
        }
      }
      return num;
    }

    int solvey() {
      int numtot=0;
      for(const auto &myPair : xsolutions ) {
        int num = solvey(myPair.first, myPair.second);
        numtot+= num*myPair.second.size();
      }
      return numtot;
    }



    long solve() {
      solvex();
      return solvey();
    }

};

int main() {
  Problem p;
  p.readInput();
  cout << p.solve() << "\n";
  cout << p.solutions.size()<< "\n";
}
