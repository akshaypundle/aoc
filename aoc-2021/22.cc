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
    struct transform {
      bool on;
      long lowx,lowy,lowz,highx,highy,highz;
    };
    struct cube {
      bool on;
      long minX,minY,minZ;
      long maxX,maxY,maxZ;
      cube(long x1,long y1, long z1, long x2, long y2, long z2, bool onoff) {
        minX  = min(x1,x2); maxX=max(x1,x2);
        minY  = min(y1,y2); maxY=max(y1,y2);
        minZ  = min(z1,z2); maxZ=max(z1,z2);
        on=onoff;
      }

      void prlong() {
        cout << minX <<".."<<maxX<<"  "<<minY<<".."<<maxY<<"  "<<minZ<<".."<<maxZ<<"\n";
      }

      long count() {
        return (maxX-minX)*(maxY-minY)*(maxZ-minZ);
      }
    };
    vector<cube> transforms;

   
    bool cube_p1[101][101][101];
    void parse(string line) {
      char ch;
      long lowx,lowy,lowz,highx,highy,highz;
      string onoff;
      stringstream ss(line);
      ss>> onoff;
      ss>>ch>>ch>>lowx>>ch>>ch>>highx>>ch>>ch>>ch>>lowy>>ch>>ch>>highy>>ch>>ch>>ch>>lowz>>ch>>ch>>highz;
      transform t;
      t.on = (onoff == "on");
      t.lowx=lowx;
      t.lowy=lowy;
      t.lowz=lowz;
      t.highx=highx;
      t.highy=highy;
      t.highz=highz;

      cube c(lowx,lowy,lowz,highx+1,highy+1,highz+1, (onoff == "on"));
      transforms.push_back(c);
/*
      for(long x=max(lowx,-50);x<=min(50,highx);x++) {
        for(long y=max(lowy,-50);y<=min(50,highy);y++) {
          for(long z=max(lowz,-50);z<=min(50,highz);z++) {
            cube_p1[x+50][y+50][z+50] = (onoff=="on"?true:false);
          }
        }
      }
*/
    }
/*

    long solve1() {
      long on=0;
      for(long x=0;x<101;x++) {
        for(long y=0;y<101;y++) {
          for(long z=0;z<101;z++) {
            if(cube_p1[x][y][z]) on++;
          }
        }
      }
      return on;
    }
*/



    bool longersect(cube a, cube b) {
      return (a.minX < b.maxX && a.maxX > b.minX) &&
        (a.minY < b.maxY && a.maxY > b.minY) &&
        (a.minZ < b.maxZ && a.maxZ > b.minZ);
    }

    // remove b from a
    vector<cube> remove(cube a, cube b) {
      vector<cube> ret;
      if(!longersect(a,b)) {
        ret.push_back(a);
        return ret;
      } 
      b = cube(min(max(b.minX, a.minX), a.maxX), min(max(b.minY, a.minY),
            a.maxY),min(max(b.minZ, a.minZ), a.maxZ),min(max(b.maxX, a.minX),
              a.maxX), min(max(b.maxY, a.minY), a.maxY), min(max(b.maxZ,
                  a.minZ), a.maxZ) , true); 
      ret.push_back(cube(a.minX,a.minY,a.minZ,b.minX,a.maxY,a.maxZ,true));
      ret.push_back(cube(b.maxX,a.minY,a.minZ,a.maxX,a.maxY,a.maxZ,true));
      ret.push_back(cube(b.minX,a.minY,a.minZ,b.maxX,b.minY,a.maxZ,true));
      ret.push_back(cube(b.minX,b.maxY,a.minZ,b.maxX,a.maxY,a.maxZ,true));
      ret.push_back(cube(b.minX,b.minY,a.minZ,b.maxX,b.maxY,b.minZ,true));
      ret.push_back(cube(b.minX,b.minY,b.maxZ,b.maxX,b.maxY,a.maxZ,true));

      return ret;
    }

    void readInput() {
      /*
      for(long x=0;x<101;x++) {
        for(long y=0;y<101;y++) {
          for(long z=0;z<101;z++) {
            cube[x][y][z] = false; 
          }
        }
      }
      */
      string line;
      while(!cin.eof()) {
        getline(cin, line);
        if(!line.empty()) parse(line);
      }
    }


    long solve2() {
      vector<cube> cubes;
      for(auto t : transforms) {
        vector<cube> newcubes;
        t.prlong();
        for(auto cube : cubes) {
          if(cube.count()>0) {
            for(auto n : remove(cube, t)) {
              if(n.count()>0){
                newcubes.push_back(n);
                n.prlong();
              }
            }
          }
        }

        if(t.on) newcubes.push_back(t);
        cubes = newcubes;
      }

      long ans=0;
      for(auto cube:cubes) ans+=cube.count();
      return ans;
    }

};

int main() {
  Problem p;
  p.readInput();
  cout << p.solve2() << "\n";
}
