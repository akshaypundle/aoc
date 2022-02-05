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
#include <tuple>
using namespace std;
using namespace library;

class Problem {
  struct point {
    int x;
    int y;
    int z;
  };
  public:
    vector<vector<point>> input;

    void readScanner() {
      string line;
      getline(cin, line);
      vector<point> newvec;

      while(!cin.eof()) {
        getline(cin, line);
        if(line.empty()) break;
        stringstream ss(line);
        point pt;
        char ch;
        ss >> pt.x >> ch >> pt.y >>ch >> pt.z;
        newvec.push_back(pt);
        //cout << pt.x << " "<<pt.y<<" "<<pt.z << "\n";
      }
      input.push_back(newvec);
      //cout << "\n";
    }

    void readInput() {
      while(!cin.eof()) {
        readScanner();
      }
    }

    point rotatePoint(point input, int config) {
      point tmppm;
      point ret;
      int pm=config/6; // 0 to 7
      int rot = config%6; // 0 to 5
      tmppm.x= pm & 4 ? input.x : -input.x;
      tmppm.y= pm & 2 ? input.y : -input.y;
      tmppm.z= pm & 1 ? input.z : -input.z;

      if(rot == 0) {
        // x,y,z
        ret.x=tmppm.x;
        ret.y=tmppm.y;
        ret.z=tmppm.z;
      } else if(rot ==1) {
        //x,z,y
        ret.x=tmppm.x;
        ret.y=tmppm.z;
        ret.z=tmppm.y;
      }else if(rot ==2) {
        //y,x,z
        ret.x=tmppm.y;
        ret.y=tmppm.x;
        ret.z=tmppm.z;
      }else if(rot ==3) {
        //y,z,x
        ret.x=tmppm.y;
        ret.y=tmppm.z;
        ret.z=tmppm.x;
      }else if(rot ==4) {
        //z,x,y
        ret.x=tmppm.z;
        ret.y=tmppm.x;
        ret.z=tmppm.y;
      }else if(rot ==5) {
        //z,y,x
        ret.x=tmppm.z;
        ret.y=tmppm.y;
        ret.z=tmppm.x;
      }

      return ret;
    }

    // base - trying
    point subtract(point base, point trying) {
      point correct;
      correct.x = base.x - trying.x;
      correct.y = base.y - trying.y;
      correct.z = base.z - trying.z;
      
      return correct;
    }

        // base - trying
    point add(point base, point trying) {
      point correct;
      correct.x = base.x + trying.x;
      correct.y = base.y + trying.y;
      correct.z = base.z + trying.z;
      
      return correct;
    }
    pair<vector<point>, point> createConfigPoints(int base_scanner, int try_scanner, int base_point , int try_point, int config) {
      vector<point> ret;
      point correction = subtract(input[base_scanner][base_point], rotatePoint(input[try_scanner][try_point], config));
      //if(config == 12 && try_point==0 && base_point==9) cout << correction.x<<","<< correction.y<<","<< correction.z<<"\n";
      for(int i=0;i<input[try_scanner].size();i++) {
        point rr=add(rotatePoint(input[try_scanner][i],config), correction);
        ret.push_back(rr);
        //if(config == 12 && try_point==0 && base_point==9) cout << rr.x<<","<<rr.y<<","<<rr.z<<"\n";
      }

      return make_pair(ret, correction);
    }

    tuple<int,int,int> totup(point pt) {
      return make_tuple(pt.x,pt.y,pt.z);
    }

    vector<point> findOverlap(set<tuple<int,int,int>> correct, vector<point> newpt) {
      int over=0;
      vector<point> overlaps;
      for(int i=0;i<newpt.size();i++) {
        tuple<int,int,int> newtup=totup(newpt[i]);
        if(correct.find(newtup) != correct.end()) {
          over++;
          overlaps.push_back(newpt[i]);
        }
      }
      return overlaps;
    }

    int configs[40][40];
    map<int,vector<point>> beacons;
    point corrections[40][40];


    // overlap config of j such that reading match i
    void findOverlapConfigs(int i, int j) {
      vector<vector<int>> working_configs;
      set<tuple<int,int,int>> correct_points;
      for(int p0=0;p0<input[i].size();p0++) { 
        correct_points.insert(totup(input[i][p0]));
      }

      for(int config=0;config<48;config++) {
        for(int p0=0;p0<input[i].size();p0++) { // the correct point in i
          for(int p1=0;p1<input[j].size();p1++) {
            pair<vector<point>,point> newpts=createConfigPoints(i,j,p0,p1,config);
            auto overlap = findOverlap(correct_points, newpts.first) ;
            if(overlap.size() >=12) {
              //vector<int> cv={i,j,p0,p1,config};
              //working_configs.push_back(cv);
              corrections[i][j]=newpts.second;
              configs[i][j]=config;
              if(beacons.find(i) != beacons.end()) {
                beacons[i]=vector<point>();
              }
              for(auto p:newpts.first) {
                beacons[i].push_back(p); // in the coordinate system of i
              }
              return;
            }
          }
        }
      }
    }

    point fuckallpoint;

    struct transform {
      int node;
      point correction;
      int config;
      transform *parent;
    };
    map<int,transform*> transforms;

    void maketransform(transform * parent) {
      if(transforms.size() == input.size()) return;
      for(int j=1;j<input.size();j++) {
        if(transforms.find(j) != transforms.end()) continue;// already found
        if(corrections[parent->node][j].x != fuckallpoint.x) {
          transform *newone = new transform();
          newone->node = j;
          newone->config=configs[parent->node][j];
          newone->correction=corrections[parent->node][j];
          newone->parent = parent;

          cout << parent->node<< " <- "<<j<<"\n";

          transforms[j]=newone;
          maketransform(newone);
        }
      }
    }


    point applyTransform(point in, int node) {
      if(node == 0) return in;
      point transformed = add(rotatePoint(in,transforms[node]->config), transforms[node]->correction);
      return applyTransform(transformed, transforms[node]->parent->node);

    }




    long solve() {
      fuckallpoint.x=98765432;
      fuckallpoint.y=98765432;
      fuckallpoint.z=98765432;
      for(int i=0;i<40;i++) {
        for(int j=0;j<40;j++) {
          corrections[i][j]=fuckallpoint;
          configs[i][j]=0;
        }
      }
      for(int i=0;i<input.size();i++) {
        for(int j=0;j<input.size();j++) {
          if(i==j) continue;
          findOverlapConfigs(i,j);
        }
        cout << "done "<<i<<"\n";
      }
      for(int i=0;i<input.size();i++) {
        for(int j=0;j<input.size();j++) {
          if(corrections[i][j].x != fuckallpoint.x) cout << i << " <- " << j<<" " << corrections[i][j].x
              <<","<<corrections[i][j].y<<","<<corrections[i][j].z<< " config "
              << configs[i][j] << "\n";
        }
      }

      transform *newone = new transform();
      newone->node = 0;
      newone->config=-1;
      newone->correction;
      newone->parent = NULL;

      transforms[0]=newone;
      maketransform(newone);

      set<tuple<int,int,int>> be;

      for(int i=0;i<input.size();i++) {
        for(int j=0;j<input[i].size();j++) {
          point p1=applyTransform(input[i][j],i);
          be.insert(totup(p1));
        }

      }
      return be.size();


    }

    int manhattan(point p1, point p2) {
      point p3 = subtract(p1,p2);
      return abs(p3.x)+abs(p3.y)+abs(p3.z);
    }

    vector<point> origins;
    int largestManhattan() {
      for(int i=0;i<input.size();i++) {
        point p;p.x=0;p.y=0;p.z=0;
        point t=applyTransform(p,i);
        origins.push_back(t);
      }

      int max=0;
      for(int i=0;i<origins.size();i++) {
        for(int j=i+1;j<origins.size();j++) {
          int d=manhattan(origins[i],origins[j]);
          if(d>max) max=d;
        }
      }
      return max;
    } 

};

int main() {
  Problem p;
  p.readInput();
  cout << p.solve() << "\n";
  cout << p.largestManhattan()<<"\n";
}
